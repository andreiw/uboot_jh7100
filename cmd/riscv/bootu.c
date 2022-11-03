// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <bootm.h>
#include <command.h>
#include <image.h>
#include <irq_func.h>
#include <lmb.h>
#include <log.h>
#include <mapmem.h>
#include <asm/global_data.h>
#include <linux/kernel.h>
#include <linux/sizes.h>

DECLARE_GLOBAL_DATA_PTR;
/*
 * Image booting support
 */
static int bootu_start(struct cmd_tbl *cmdtp, int flag, int argc,
		       char *const argv[], struct bootm_headers *images)
{
	int ret;
	ulong ld;
	ulong image_size;
	char *arg0_end;

	debug("image_load_addr is 0x%lx\n", image_load_addr);
	ret = do_bootm_states(cmdtp, flag, argc, argv, BOOTM_STATE_START,
			      images, 1);

	/* Setup Linux kernel Image entry point */
	if (argc > 0) {
		ld = hextoul(argv[0], NULL);
		debug("*  bootu: cmdline image address = 0x%08lx\n", ld);
	} else {
		ld = image_load_addr;
		debug("*  bootu: default image load address = 0x%08lx\n",
		      image_load_addr);
	}

	arg0_end = strchr(argv[0], ':');
	if (arg0_end != NULL) {
		image_size = hextoul(++arg0_end, NULL);
	} else {
		image_size = env_get_ulong("filesize", 16, 0);
	}
	debug("*  bootu: size = 0x%08lx\n", image_size);

	if (image_size == 0) {
		debug("image size unknown\n");
		return -EINVAL;
	}

	images->ep = ld;
	images->os.start = ld;
	images->os.end = images->os.start  + image_size;

#if CONFIG_IS_ENABLED(OF_LIBFDT)
	if (argc > 1) {
		images->ft_addr = (void *) hextoul(argv[1], NULL);
	} else {
		images->ft_addr = (void *) gd->fdt_blob;
	}
	images->ft_len = fdt_totalsize(images->ft_addr);

	if (CONFIG_IS_ENABLED(CMD_FDT)) {
		set_working_fdt_addr(map_to_sysmem(images->ft_addr));
	}
#endif

	lmb_reserve(&images->lmb, images->ep, le32_to_cpu(image_size));

	return 0;
}

int do_bootu_cmd(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	int ret;

	/* Consume 'bootu' */
	argc--; argv++;

	if (bootu_start(cmdtp, flag, argc, argv, &images))
		return 1;

	/*
	 * We are doing the BOOTM_STATE_LOADOS state ourselves, so must
	 * disable interrupts ourselves
	 */
	bootm_disable_interrupts();

	images.os.os = IH_OS_BOOTU;
	images.os.arch = IH_ARCH_RISCV;
	ret = do_bootm_states(cmdtp, flag, argc, argv,
			      BOOTM_STATE_OS_PREP | BOOTM_STATE_OS_FAKE_GO |
			      BOOTM_STATE_OS_GO,
			      &images, 1);

	return ret;
}

#ifdef CONFIG_SYS_LONGHELP
static char bootu_help_text[] =
	"[addr[:size]] [fdt]]\n"
	"    - boot RV blob, such as another U-Boot binary, at 'addr'\n"
	"\ta0: hart id\n"
	"\ta1: fdt address\n"
	"";
#endif

U_BOOT_CMD(
	bootu,	CONFIG_SYS_MAXARGS,	1,	do_bootu_cmd,
	"boot RV blob from memory", bootu_help_text
);
