// SPDX-License-Identifier: GPL-2.0+
/*
 *  EFI application ACPI tables support
 *
 *  Copyright (C) 2018, Bin Meng <bmeng.cn@gmail.com>
 */

#include <common.h>
#include <efi_loader.h>
#include <log.h>
#include <mapmem.h>
#include <acpi/acpi_table.h>

#ifdef CONFIG_CPU_RISCV
#define MAX_ACPI_ADDR U64_MAX
#else
/*
 * x86: Map within the low 32 bits, to allow for 32bit ACPI tables.
 */
#define MAX_ACPI_ADDR U32_MAX
#endif

static const efi_guid_t acpi_guid = EFI_ACPI_TABLE_GUID;

/*
 * Install the ACPI table as a configuration table.
 *
 * Return:	status code
 */
efi_status_t efi_acpi_register(void)
{
	u64 acpi = MAX_ACPI_ADDR;
	efi_status_t ret;
	size_t len;
	ulong addr;

	/* Reserve 64kiB page for ACPI */
	ret = efi_allocate_pages(EFI_ALLOCATE_MAX_ADDRESS,
				 EFI_ACPI_RECLAIM_MEMORY,
				 CONFIG_GENERATE_ACPI_TABLE_PAGES,
				 &acpi);
	if (ret != EFI_SUCCESS)
		return ret;

	/*
	 * Generate ACPI tables - we know that efi_allocate_pages() returns
	 * a 4k-aligned address, so it is safe to assume that
	 * write_acpi_tables() will write the table at that address.
	 */
	addr = map_to_sysmem((void *)(ulong)acpi);
	len = EFI_PAGE_SIZE * CONFIG_GENERATE_ACPI_TABLE_PAGES;
	write_acpi_tables(addr, addr + len - 1);

	/* And expose them to our EFI payload */
	return efi_install_configuration_table(&acpi_guid,
					       (void *)(uintptr_t)acpi);
}
