// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Shanghai StarFive Technology Co., Ltd.
 * Micheal Zhu <michael.zhu@starfivetech.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <version.h>
#include <linux/sizes.h>

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS		16

#define CONFIG_SYS_SDRAM_BASE		0x80000000
/* Init Stack Pointer */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_STANDALONE_LOAD_ADDR	(CONFIG_SYS_SDRAM_BASE + SZ_2M)

/*mac addr offset in otp*/
#define STARFIVE_OTP_MAC_OFFSET		0x28

/*
 * Ethernet
 */
#if CONFIG_IS_ENABLED(CMD_NET)
#define CONFIG_DW_ALTDESCRIPTOR
#endif

/* HACK these should have '#if defined (stuff) around them like zynqp*/
#define BOOT_TARGET_DEVICES(func)	func(DHCP, dhcp, na) \
					func(MMC, mmc, 0)

#include <config_distro_bootcmd.h>

#include <environment/distro/sf.h>

#define STARLIGHT_FEDORA_BOOTENV \
	"bootdir=/boot\0" \
	"bootenv=uEnv.txt\0" \
	"mmcdev=0\0" \
	"mmcpart=3\0"

#define STARLIGHT_TEST_BOOTENV \
	"testpart=0:1\0" \
	"testenv=u74_uEnv.txt\0" \
	"mmcsetup=mmc part\0" \
	"fdtsetup=fdt addr ${fdtcontroladdr}\0" \
	"fatenv=fatload mmc ${testpart} ${loadaddr} ${testenv};" \
		"env import -t ${loadaddr} ${filesize}\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	STARLIGHT_FEDORA_BOOTENV \
	"loadaddr=0xa0000000\0" \
	STARLIGHT_TEST_BOOTENV \
	"loadbootenv=fatload mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"ext4bootenv=ext4load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc${mmcdev} ...; " \
		"env import -t ${loadaddr} ${filesize}\0" \
	"mmcbootenv=setenv bootpart ${mmcdev}:${mmcpart}; " \
		"mmc dev ${mmcdev}; " \
		"if mmc rescan; then " \
			"run loadbootenv && run importbootenv; " \
			"run ext4bootenv && run importbootenv; " \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...; " \
				"run uenvcmd; " \
			"fi; " \
		"fi\0" \
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
	BOOTENV \
	BOOTENV_SF

#define CONFIG_SYS_MAX_FLASH_SECT	0
#define CONFIG_SYS_MAX_FLASH_BANKS	0
#define __io

#endif /* __CONFIG_H */
