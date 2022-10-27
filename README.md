U-Boot for StarFive JH7100-based boards
=======================================

This is a private rebase of https://github.com/starfive-tech/u-boot
on top of latest U-Boot, with further fixes/work.

Tested on the Starlight aka BeagleV.

Why
===

Maybe you want:
- Newer U-Boot code than 2022.01-rc4?
- Working ethernet?
- Working USB3 boot?
- All known fixes pulled from https://github.com/starfive-tech pull requests and branches.

 Building
========

- Clone https://github.com/riscv/opensbi.git
- Clone https://github.com/andreiw/uboot_jh7100
- wget https://raw.githubusercontent.com/starfive-tech/freelight-u-sdk/JH7100_VisionFive/fsz.sh

```
export BUILD_PLATFORM=starlight # starlight for BeagleV, visionfive for VisionFive V1
pushd uboot_jh7100
make starfive_jh7100_$(BUILD_PLATFORM)_smode_defconfig ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-
make u-boot.bin u-boot.dtb ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-
popd
pushd opensbi
make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- PLATFORM=generic FW_PAYLOAD_PATH=../uboot_jh7100/u-boot.bin FW_FDT_PATH=../uboot_jh7100/u-boot.dtb
cp build/platform/generic/firmware/fw_payload.bin ../fw_payload.bin
popd
 ./fsz.sh fw_payload.bin fw_payload.bin.out
```

Flashing
========

Follow https://starfivetech.com/uploads/VisionFive%20Single%20Board%20Computer%20Quick%20Start%20Guide.pdf

Now what?
=========

On first boot, interrupt the booting by pressing 'v', and:
```
# env default -a
# saveenv
```

To boot the live image Ubuntu via USB3, you'll need to somehow update the initramfs. This is easiest to do if you first boot the same system from SD card, chroot and update-initramfs.

The live installer image does not work at the moment.
