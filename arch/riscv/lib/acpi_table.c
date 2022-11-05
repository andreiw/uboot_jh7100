// SPDX-License-Identifier: GPL-2.0+
/*
 * Based on acpi_table.c from arch/x86/lib
 */

#define LOG_CATEGORY LOGC_ACPI

#include <common.h>
#include <cpu.h>
#include <dm.h>
#include <log.h>
#include <dm/uclass-internal.h>
#include <mapmem.h>
#include <serial.h>
#include <acpi/acpigen.h>
#include <acpi/acpi_device.h>
#include <acpi/acpi_table.h>
#include <tables_csum.h>
#include <asm/global_data.h>
#include <dm/acpi.h>
#include <linux/err.h>

#define CPU_UID(plat) ((plat)->cpu_id)
#define S_MODE_EXT_INTERRUPT 9

int acpi_write_spcr(struct acpi_ctx *ctx, const struct acpi_writer *entry)
{
	struct serial_device_info serial_info = {0};
	ulong serial_address, serial_offset;
	struct acpi_table_header *header;
	struct acpi_spcr *spcr;
	struct udevice *dev;
	uint serial_config;
	uint serial_width;
	int access_size;
	int space_id;
	int ret = -ENODEV;

	spcr = ctx->current;
	header = &spcr->header;

	memset(spcr, '\0', sizeof(struct acpi_spcr));

	/* Fill out header fields */
	acpi_fill_header(header, "SPCR");
	header->length = sizeof(struct acpi_spcr);
	header->revision = 3;

	/* Read the device once, here. It is reused below */
	dev = gd->cur_serial_dev;
	if (dev)
		ret = serial_getinfo(dev, &serial_info);
	if (ret)
		serial_info.type = SERIAL_CHIP_UNKNOWN;

	/* Encode chip type */
	switch (serial_info.type) {
	case SERIAL_CHIP_16550_COMPATIBLE:
		spcr->interface_type = ACPI_DBG2_16550_GAS;
		break;
	case SERIAL_CHIP_UNKNOWN:
	default:
		spcr->interface_type = ACPI_DBG2_UNKNOWN;
		break;
	}

	/* Encode address space */
	switch (serial_info.addr_space) {
	case SERIAL_ADDRESS_SPACE_MEMORY:
		space_id = ACPI_ADDRESS_SPACE_MEMORY;
		break;
	case SERIAL_ADDRESS_SPACE_IO:
	default:
		space_id = ACPI_ADDRESS_SPACE_IO;
		break;
	}

	serial_width = serial_info.reg_width * 8;
	serial_offset = serial_info.reg_offset << serial_info.reg_shift;
	serial_address = serial_info.addr + serial_offset;

	/* Encode register access size */
	switch (serial_info.reg_shift) {
	case 0:
		access_size = ACPI_ACCESS_SIZE_BYTE_ACCESS;
		break;
	case 1:
		access_size = ACPI_ACCESS_SIZE_WORD_ACCESS;
		break;
	case 2:
		access_size = ACPI_ACCESS_SIZE_DWORD_ACCESS;
		break;
	case 3:
		access_size = ACPI_ACCESS_SIZE_QWORD_ACCESS;
		break;
	default:
		access_size = ACPI_ACCESS_SIZE_UNDEFINED;
		break;
	}

	debug("UART type %u @ %lx\n", spcr->interface_type, serial_address);

	/* Fill GAS */
	spcr->serial_port.space_id = space_id;
	spcr->serial_port.bit_width = serial_width;
	spcr->serial_port.bit_offset = 0;
	spcr->serial_port.access_size = access_size;
	spcr->serial_port.addrl = lower_32_bits(serial_address);
	spcr->serial_port.addrh = upper_32_bits(serial_address);

	/* Encode baud rate */
	switch (serial_info.baudrate) {
	case 9600:
		spcr->baud_rate = 3;
		break;
	case 19200:
		spcr->baud_rate = 4;
		break;
	case 57600:
		spcr->baud_rate = 6;
		break;
	case 115200:
		spcr->baud_rate = 7;
		break;
	default:
		spcr->baud_rate = 0;
		break;
	}

	serial_config = SERIAL_DEFAULT_CONFIG;
	if (dev)
		ret = serial_getconfig(dev, &serial_config);

	spcr->parity = SERIAL_GET_PARITY(serial_config);
	spcr->stop_bits = SERIAL_GET_STOP(serial_config);

	/* No PCI devices for now */
	spcr->pci_device_id = 0xffff;
	spcr->pci_vendor_id = 0xffff;

	if (serial_info.clock == 0) {
		/*
		 * We don't know the clock, so let the OS know it shouldn't
		 * touch the configuration of the serial device.
		 */
		spcr->baud_rate = 0;
	} else {
		spcr->clock_frequency = serial_info.clock;
	}

	/* Fix checksum */
	header->checksum = table_compute_checksum((void *)spcr, header->length);

	acpi_add_table(ctx, spcr);
	acpi_inc(ctx, spcr->header.length);

	return 0;
}
ACPI_WRITER(5spcr, "SPCR", acpi_write_spcr, 0);

__weak int acpi_fill_fadt(struct acpi_ctx *ctx,
			  struct acpi_fadt *fadt)
{
	return 0;
}

static int acpi_write_fadt(struct acpi_ctx *ctx,
			   const struct acpi_writer *entry)
{
	int ret;
	struct acpi_fadt *fadt = ctx->current;
	struct acpi_table_header *header = &fadt->header;

	memset((void *)fadt, '\0', sizeof(struct acpi_fadt));
	acpi_fill_header(header, "FACP");
	header->length = sizeof(struct acpi_fadt);

	memcpy(header->oem_id, OEM_ID, 6);
	memcpy(header->oem_table_id, OEM_TABLE_ID, 8);
	memcpy(header->aslc_id, ASLC_ID, 4);
	header->aslc_revision = 1;

	/* Use ACPI 6.5 revision */
	fadt->header.revision = ACPI_FADT_REV_ACPI_6_0;
	fadt->minor_revision = 5;

	fadt->preferred_pm_profile = ACPI_PM_UNSPECIFIED;
	fadt->flags = ACPI_FADT_HW_REDUCED_ACPI;
	/* fadt->flags |= ACPI_FADT_HEADLESS; */

	fadt->x_dsdt_l = (unsigned long) ctx->dsdt;
	fadt->x_dsdt_h = ((unsigned long) ctx->dsdt >> 32);

	/* Allow a board override. */
	ret = acpi_fill_fadt(ctx, fadt);
	if (ret != 0) {
		return ret;
	}

	/* Fix checksum */
	header->checksum = table_compute_checksum(fadt, header->length);

	acpi_add_table(ctx, fadt);
	acpi_inc(ctx, sizeof(struct acpi_fadt));

	return 0;
}
ACPI_WRITER(5fact, "FADT", acpi_write_fadt, 0);

int acpi_patch_rintc_ic_id(uintptr_t rintc, uint32_t acpi_uid,
			   uint32_t ic_id)
{
	struct acpi_madt_rintc *r = (void *) rintc;

	while (r->type == ACPI_APIC_RINTC) {
		if (r->acpi_uid == acpi_uid) {
			r->ic_id = ic_id;
			return 0;
		}

		r++;
	}

	return -EINVAL;
}

uintptr_t acpi_fill_madt_plic_each(uintptr_t rintc, uintptr_t last,
				   uintptr_t current, ofnode node)
{
	int i;
	int ret;
	int contexts;
	u32 ndev;
	u32 max_priority;
	struct acpi_madt_plic *last_plic = (void *) last;
	struct acpi_madt_plic *plic = (void *) current;

	assert(ofnode_valid(node));

	contexts = ofnode_count_phandle_with_args(node, "interrupts-extended", "#interrupt-cells", 0);
	if (contexts <= 0) {
		return current;
	}

	if (ofnode_read_u32(node, "riscv,ndev", &ndev) != 0) {
		pr_err("couldn't read riscv,ndev\n");
		return current;
	}
	if (ofnode_read_u32(node, "riscv,max-priority", &max_priority) != 0) {
		pr_err("couldn't read riscv,max-priority\n");
		return current;
	}

	memset(plic, 0, sizeof(*plic));
	plic->type = ACPI_APIC_PLIC;
	plic->length = sizeof(*plic);
	plic->version = 1;
	if (last_plic == NULL) {
		plic->id = 0;
	} else {
		plic->id = last_plic->id + 1;
	}
	strcpy(&plic->man_id[0], "PLIC0");
	plic->regs_size = 0;
	if (last_plic == NULL) {
		plic->gsiv_base = 0;
	} else {
		plic->gsiv_base = last_plic->gsiv_base + last_plic->ndev + 1;
	}
	plic->flags = 0;
	plic->ndev = ndev;
	plic->max_priority = max_priority;
	plic->reg_base = ofnode_get_addr(node);
	plic->regs_size = ofnode_get_size(node);

	for (i = 0; i < contexts; i++) {
		ofnode cpu_node;
		struct ofnode_phandle_args args;
		struct cpu_plat *cpu_plat;
		struct udevice *dev = NULL;

		ret = ofnode_parse_phandle_with_args(node, "interrupts-extended",
						     "#interrupt-cells", 0, i, &args);
		if (ret != 0) {
			pr_err("couldn't parse for index %i\n", i);
			continue;
		}

		if (args.args_count < 1) {
			pr_err("bad args count for index %i\n", i);
			continue;
		}

		cpu_node = ofnode_get_parent(args.node);
		uclass_find_device_by_ofnode(UCLASS_CPU, cpu_node, &dev);
		if (dev == NULL) {
			/*
			 * Some SoCs may have non-application cores, and these
			 * aren't used by the firmware or OS.
			 */
			continue;
		}

		cpu_plat = dev_get_parent_plat(dev);
		if (args.args[0] == S_MODE_EXT_INTERRUPT) {
			acpi_patch_rintc_ic_id(rintc, CPU_UID(cpu_plat),
					       (plic->id << 24) | i);
		}
	}

	return (uintptr_t) (plic + 1);
}

uintptr_t acpi_fill_madt_plic(uintptr_t rintc, uintptr_t current)
{
	uintptr_t last = 0;
	ofnode node = ofnode_by_compatible(ofnode_null(), "riscv,plic0");

	if (!ofnode_valid(node)) {
		return current;
	}

	do {
		current = acpi_fill_madt_plic_each(rintc, last, current, node);
		last = current;
	} while (ofnode_valid(node = ofnode_by_compatible(node, "riscv, plic0")));

	return current;
}

uintptr_t acpi_fill_madt_rintc(uintptr_t current)
{
	struct udevice *dev;
	struct cpu_plat *plat;

	uclass_find_first_device(UCLASS_CPU, &dev);
	if (!dev) {
		debug("madt: unable to find RISC-V cpu device\n");
		return current;
	}

	/*
	 * This only works if all possible CPUs are on. Otherwise,
	 * use ofnode_for_each_subnode(node, dev_ofnode(dev->parent))
	 * and manually parse similar to riscv_cpu.c.
	 */
	do {
		struct acpi_madt_rintc *r = (void *) current;
		plat = dev_get_parent_plat(dev);

		memset(r, 0, sizeof(*r));

		r->type = ACPI_APIC_RINTC;
		r->length = sizeof(*r);
		r->version = 1;
		r->hart_id = plat->cpu_id;
		/*
		 * Assume _UID is same as hartid, which may fail
		 * for non-trivial SoC implementations. Anyway, this
		 * can get patched by acpi_fill_madt.
		 */
		r->acpi_uid = CPU_UID(plat);
		r->flags = ACPI_MADT_RINTCF_ENABLED;
		current = (uintptr_t) (r + 1);
	} while ((uclass_find_next_device(&dev) == 0) && (dev != NULL));

	return current;
}

__weak uintptr_t acpi_fill_madt(struct acpi_madt *madt, uintptr_t current)
{
	return current;
}

int acpi_write_madt(struct acpi_ctx *ctx, const struct acpi_writer *entry)
{
	struct acpi_table_header *header;
	struct acpi_madt *madt;
	uintptr_t current;
	uintptr_t rintc;

	madt = ctx->current;

	memset(madt, '\0', sizeof(struct acpi_madt));
	header = &madt->header;

	/* Fill out header fields */
	acpi_fill_header(header, "APIC");
	header->length = sizeof(struct acpi_madt);
	header->revision = ACPI_MADT_REV_ACPI_6_5;

	rintc = (uintptr_t) madt + sizeof(struct acpi_madt);
	current = acpi_fill_madt_rintc(rintc);
	current = acpi_fill_madt_plic(rintc, current);

	/* Allow a board override. */
	current = acpi_fill_madt(madt, current);

	/* (Re)calculate length and checksum */
	header->length = current - (uintptr_t) madt;

	header->checksum = table_compute_checksum((void *)madt, header->length);
	acpi_add_table(ctx, madt);
	acpi_inc(ctx, madt->header.length);

	return 0;
}
ACPI_WRITER(5madt, NULL, acpi_write_madt, 0);
