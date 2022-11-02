// SPDX-License-Identifier: GPL-2.0

#include <clk.h>
#include <common.h>
#include <display.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/uclass-internal.h>
#include <log.h>
#include <regmap.h>
#include <video.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <dm/device_compat.h>
#include <env.h>
#include <cpu_func.h>
#include "starfive.h"

#define LCDC_PRT(...)

DECLARE_GLOBAL_DATA_PTR;

struct fwcon_priv {
	struct clk clk_vout_src;
	void *base_lcdc;
	void *base_clk;
	struct display_timing timing;
	struct video_priv *video_uc_priv;
	struct video_uc_plat *video_uc_plat;
	enum WIN_FMT pixel_format;
	int win_num;
};

static u32 sf_fb_lcdcread32(struct fwcon_priv *sf_dev, u32 reg)
{
	return readl(sf_dev->base_lcdc + reg);
}

static void sf_fb_lcdcwrite32(struct fwcon_priv *sf_dev, u32 reg, u32 val)
{
	writel(val, sf_dev->base_lcdc + reg);
}

void lcdc_mode_cfg(struct fwcon_priv *sf_dev, uint32_t workMode,
		   int dotEdge, int syncEdge, int r2yBypass,
		   int srcSel, int intSrc, int intFreq)
{
	u32 lcdcEn = 0x1;
	u32 cfg = lcdcEn | workMode << LCDC_WORK_MODE
		| dotEdge << LCDC_DOTCLK_P
		| syncEdge << LCDC_HSYNC_P
		| syncEdge << LCDC_VSYNC_P
		| 0x0 << LCDC_DITHER_EN
		| r2yBypass << LCDC_R2Y_BPS
		| srcSel << LCDC_TV_LCD_PATHSEL
		| intSrc << LCDC_INT_SEL
		| intFreq << LCDC_INT_FREQ;

	sf_fb_lcdcwrite32(sf_dev, LCDC_GCTRL, cfg);
	LCDC_PRT("LCDC WorkMode: 0x%x, LCDC Path: %d\n", workMode, srcSel);
}

void lcdc_timing_cfg(struct fwcon_priv *sf_dev, int vunit)
{
	int hpw = sf_dev->timing.hsync_len.typ - 1;
	int hbk = sf_dev->timing.hsync_len.typ +
          sf_dev->timing.hback_porch.typ;
	int hfp = sf_dev->timing.hfront_porch.typ;
	int vpw = sf_dev->timing.vsync_len.typ - 1;
	int vbk = sf_dev->timing.vsync_len.typ +
          sf_dev->timing.vback_porch.typ;
	int vfp = sf_dev->timing.vfront_porch.typ;

	int htiming = hbk | (hfp << LCDC_RGB_HFP);
	int vtiming = vbk | (vfp << LCDC_RGB_VFP);
	int hvwid = hpw | (vpw << LCDC_RGB_VPW) | (vunit << LCDC_RGB_UNIT);

	sf_fb_lcdcwrite32(sf_dev, LCDC_RGB_H_TMG, htiming);
	sf_fb_lcdcwrite32(sf_dev, LCDC_RGB_V_TMG, vtiming);
	sf_fb_lcdcwrite32(sf_dev, LCDC_RGB_W_TMG, hvwid);
	LCDC_PRT("LCDC HPW: %d, HBK: %d, HFP: %d\n", hpw, hbk, hfp);
	LCDC_PRT("LCDC VPW: %d, VBK: %d, VFP: %d\n", vpw, vbk, vfp);
	LCDC_PRT("LCDC V-Unit: %d, 0-HSYNC and 1-dotClk period\n", vunit);
}

void lcdc_desize_cfg(struct fwcon_priv *sf_dev)
{
	int hsize = sf_dev->video_uc_priv->xsize - 1;
	int vsize = sf_dev->video_uc_priv->ysize - 1;

	int sizecfg = hsize | (vsize << LCDC_BG_VSIZE);
	sf_fb_lcdcwrite32(sf_dev, LCDC_BACKGROUD, sizecfg);
	LCDC_PRT("LCDC Dest H-Size: %d, V-Size: %d\n", hsize, vsize);
}

void lcdc_rgb_dclk_cfg(struct fwcon_priv *sf_dev, int dot_clk_sel)
{
	int cfg = dot_clk_sel << 16;

	sf_fb_lcdcwrite32(sf_dev, LCDC_RGB_DCLK, cfg);
	LCDC_PRT("LCDC Dot_clock_output_sel: 0x%x\n", cfg);
}

void lcdc_win_cfgA(struct fwcon_priv *sf_dev, int winNum,
		   int layEn, int clorTab,
		   int colorEn, int addrMode, int lock)
{
	int cfg;
	int hsize = sf_dev->video_uc_priv->xsize - 1;
	int vsize = sf_dev->video_uc_priv->ysize - 1;
	int srcSel_v = LCDC_WIN_ISSEL_DDR;

	cfg = hsize | vsize << LCDC_WIN_VSIZE | layEn << LCDC_WIN_EN |
		clorTab << LCDC_CC_EN | colorEn << LCDC_CK_EN |
		srcSel_v << LCDC_WIN_ISSEL | addrMode << LCDC_WIN_PM |
		lock << LCDC_WIN_CLK;

	sf_fb_lcdcwrite32(sf_dev, LCDC_WIN0_CFG_A + winNum * 0xC, cfg);
	LCDC_PRT("LCDC Win%d H-Size: %d, V-Size: %d, layEn: %d, Src: %d, AddrMode: %d\n",
		winNum, hsize, vsize, layEn, srcSel_v, addrMode);
}

void lcdc_win_cfgB(struct fwcon_priv *sf_dev, int winNum, int xpos, int ypos,
		   int argbOrd)
{
	int win_format = 0;
	int cfg = xpos | ypos << LCDC_WIN_VPOS;

	win_format = sf_dev->pixel_format;
	LCDC_PRT("LCDC win_format: 0x%x\n",win_format);

	cfg |= win_format << LCDC_WIN_FMT | argbOrd << LCDC_WIN_ARGB_ORDER;

	sf_fb_lcdcwrite32(sf_dev, LCDC_WIN0_CFG_B + winNum * 0xC, cfg);
	LCDC_PRT("LCDC Win%d Xpos: %d, Ypos: %d, win_format: 0x%x, ARGB Order: 0x%x\n",
		 winNum, xpos, ypos, win_format, argbOrd);
}

void lcdc_win_cfgC(struct fwcon_priv *sf_dev, int winNum, int colorKey)
{
	sf_fb_lcdcwrite32(sf_dev, LCDC_WIN0_CFG_C + winNum * 0xC, colorKey);
	LCDC_PRT("LCDC Win%d Color Key: 0x%6x\n", winNum, colorKey);
}

void lcdc_win_srcSize(struct fwcon_priv *sf_dev, int winNum)
{
	int addr, off, winsize, preCfg, cfg;
	int hsize = sf_dev->video_uc_priv->xsize - 1;

	switch(winNum) {
	case 0 : {addr = LCDC_WIN01_HSIZE; off = 0xfffff000; winsize = hsize; break;}
	case 1 : {addr = LCDC_WIN01_HSIZE; off = 0xff000fff; winsize = hsize << LCDC_IMG_HSIZE; break;}
	case 2 : {addr = LCDC_WIN23_HSIZE; off = 0xfffff000; winsize = hsize; break;}
	case 3 : {addr = LCDC_WIN23_HSIZE; off = 0xff000fff; winsize = hsize << LCDC_IMG_HSIZE; break;}
	case 4 : {addr = LCDC_WIN45_HSIZE; off = 0xfffff000; winsize = hsize; break;}
	case 5 : {addr = LCDC_WIN45_HSIZE; off = 0xff000fff; winsize = hsize << LCDC_IMG_HSIZE; break;}
	case 6 : {addr = LCDC_WIN67_HSIZE; off = 0xfffff000; winsize = hsize; break;}
	case 7 : {addr = LCDC_WIN67_HSIZE; off = 0xff000fff; winsize = hsize << LCDC_IMG_HSIZE; break;}
	default: {addr = LCDC_WIN01_HSIZE; off = 0xfffff000; winsize = hsize; break;}
	}
	preCfg = sf_fb_lcdcread32(sf_dev, addr)  & off;
	cfg = winsize | preCfg;
	sf_fb_lcdcwrite32(sf_dev, addr, cfg);
	LCDC_PRT("LCDC Win%d Src Hsize: %d\n", winNum, hsize);
}

void lcdc_alphaVal_cfg(struct fwcon_priv *sf_dev, int val1, int val2, int val3,
		       int val4, int sel)
{
	int val = val1 | val2 << LCDC_ALPHA2
		| val3 << LCDC_ALPHA3
		| val4 << LCDC_ALPHA4
		| sel << LCDC_01_ALPHA_SEL;

	int preVal = 0xfffb0000 & sf_fb_lcdcread32(sf_dev, LCDC_ALPHA_VALUE);
	sf_fb_lcdcwrite32(sf_dev, LCDC_ALPHA_VALUE, preVal | val);
	LCDC_PRT("LCDC Alpha 1: %x, 2: %x, 3: %x, 4: %x\n", val1, val2, val3, val4);
}

void lcdc_panel_cfg(struct fwcon_priv *sf_dev, int buswid, int depth,
		    int txcycle, int pixpcycle,
		    int rgb565sel, int rgb888sel)
{
	int cfg = buswid | depth << LCDC_COLOR_DEP
			  | txcycle << LCDC_TCYCLES
			  | pixpcycle << LCDC_PIXELS
			  | rgb565sel << LCDC_565RGB_SEL
			  | rgb888sel << LCDC_888RGB_SEL;

	sf_fb_lcdcwrite32(sf_dev, LCDC_PANELDATAFMT, cfg);
	LCDC_PRT("LCDC bus bit: :%d, pixDep: 0x%x, txCyle: %d, %dpix/cycle, RGB565 2cycle_%d, RGB888 3cycle_%d\n",
		 buswid, depth, txcycle, pixpcycle, rgb565sel, rgb888sel);
}

void lcdc_win02Addr_cfg(struct fwcon_priv *sf_dev, int addr0, int addr1)
{
	sf_fb_lcdcwrite32(sf_dev, LCDC_WIN0STARTADDR0 + sf_dev->win_num * 0x8, addr0);
	sf_fb_lcdcwrite32(sf_dev, LCDC_WIN0STARTADDR1 + sf_dev->win_num * 0x8, addr1);
	LCDC_PRT("LCDC Win%d Start Addr0: 0x%8x, Addr1: 0x%8x\n", sf_dev->win_num, addr0, addr1);
}

static int lcdc_win_sel(enum lcdc_in_mode sel)
{
	assert (sel == LCDC_IN_LCD_AXI);


	return LCDC_WIN_0;
}

void lcdc_config(struct fwcon_priv *sf_dev)
{
	int winNum = sf_dev->win_num;

	lcdc_mode_cfg(sf_dev, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0);
	lcdc_timing_cfg(sf_dev, 0);
	lcdc_desize_cfg(sf_dev);
	lcdc_rgb_dclk_cfg(sf_dev, 0x1);

	lcdc_win02Addr_cfg(sf_dev, sf_dev->video_uc_plat->base, 0x0);

	lcdc_win_cfgA(sf_dev, winNum, 0x1, 0x0, 0x0, 0x0, 0x0);
	lcdc_win_cfgB(sf_dev, winNum, 0x0, 0x0, 0x0);
	lcdc_win_cfgC(sf_dev, winNum, 0xffffff);

	lcdc_win_srcSize(sf_dev, winNum);
	lcdc_alphaVal_cfg(sf_dev, 0xf, 0xf, 0xf, 0xf, 0x0);
	lcdc_panel_cfg(sf_dev, 0x3, 0x4, 0x0, 0x0, 0x0, 0x1);
}

void lcdc_run(struct fwcon_priv *sf_dev, int winNum, uint32_t lcdTrig)
{
	uint32_t runcfg = sf_dev->win_num << LCDC_EN_CFG_MODE | lcdTrig;
	sf_fb_lcdcwrite32(sf_dev, LCDC_SWITCH, runcfg);
	LCDC_PRT("Start run LCDC\n");
}

static u32 sf_fb_clkread32(struct fwcon_priv *sf_dev, u32 reg)
{
	return readl(sf_dev->base_clk + reg);
}

static void sf_fb_clkwrite32(struct fwcon_priv *sf_dev, u32 reg, u32 val)
{
	writel(val, sf_dev->base_clk + reg);
}

static int sf_fb_lcdc_clk_cfg(struct fwcon_priv *sf_dev)
{
	u32 tmp_val = 0;
	u32 reg_val = clk_get_rate(&sf_dev->clk_vout_src) /
		sf_dev->timing.pixelclock.typ;

	tmp_val = sf_fb_clkread32(sf_dev, CLK_LCDC_OCLK_CTRL);
	tmp_val &= ~(0x3F);
	tmp_val |= (reg_val & 0x3F);
	sf_fb_clkwrite32(sf_dev, CLK_LCDC_OCLK_CTRL, tmp_val);

	return 0;
}

static int fwcon_bind(struct udevice *dev)
{
	int ret;
	u32 fb_phandle;
	ofnode fb_node;
	ofnode disp_node;
	struct video_uc_plat *plat = dev_get_uclass_plat(dev);

	disp_node = dev_ofnode(dev);
	ret = ofnode_read_u32(disp_node, "memory-region", &fb_phandle);
	if (ret != 0) {
		dev_err(dev, "couldn't find fb memory-region phandle\n");
		return ret;
	}

	fb_node = ofnode_get_by_phandle(fb_phandle);
	if (!ofnode_valid(fb_node)) {
		dev_err(dev, "bad fb memory-region phandle\n");
		return ret;
	}

	plat->size = ofnode_get_size(fb_node);
	plat->base = ofnode_get_addr(fb_node);
	return 0;
}

static int fwcon_probe(struct udevice *dev)
{
	int ret;
	u32 disp_phandle;
	ofnode disp_node;
	struct udevice *disp = NULL;
	struct display_plat *disp_uc_plat = NULL;
	ofnode node = dev_ofnode(dev);
	struct fwcon_priv *priv = dev_get_priv(dev);
	struct video_priv *video_uc_priv = dev_get_uclass_priv(dev);
	struct video_uc_plat *video_uc_plat = dev_get_uclass_plat(dev);

	/* Before relocation we don't need to do anything */
	if (!(gd->flags & GD_FLG_RELOC)) {
		return 0;
	}

	ret = clk_get_by_name(dev, "vout_src", &priv->clk_vout_src);
	if (ret != 0) {
		dev_err(dev, "couldn't get vout_src clock\n");
	}

	priv->base_lcdc = dev_remap_addr_name(dev, "lcdc");
	if (priv->base_lcdc == NULL) {
		dev_err(dev, "bad base_lcdc\n");
		return -EINVAL;
	}

	priv->base_clk = dev_remap_addr_name(dev, "clk");
	if (priv->base_clk == NULL) {
		dev_err(dev, "bad base_clk\n");
		return -EINVAL;
	}

	ret = ofnode_read_u32(node, "display", &disp_phandle);
	if (ret != 0) {
		dev_err(dev, "couldn't find display phandle\n");
		return ret;
	}

	disp_node = ofnode_get_by_phandle(disp_phandle);
	if (!ofnode_valid(disp_node)) {
		dev_err(dev, "bad display phandle\n");
		return -EINVAL;
	}

	uclass_find_device_by_ofnode(UCLASS_DISPLAY, disp_node, &disp);
	if (disp == NULL) {
		dev_err(dev, "couldn't find display udevice\n");
		return -EINVAL;
	}

	disp_uc_plat = dev_get_uclass_plat(disp);
	if (display_in_use(disp)) {
		return -EBUSY;
	}

	disp_uc_plat->src_dev = dev;
	ret = device_probe(disp);
	if (ret) {
		dev_err(dev, "display '%s' won't probe: %d\n",
		       disp->name, ret);
		return ret;
	}

	ret = display_read_timing(disp, &priv->timing);
	if (ret) {
		dev_err(dev, "failed to read timings: %d\n", ret);
		return ret;
	}

	priv->video_uc_priv = video_uc_priv;
	priv->video_uc_plat = video_uc_plat;
	video_uc_priv->xsize = roundup(priv->timing.hactive.typ, 16);
	video_uc_priv->ysize = priv->timing.vactive.typ;

	if (env_get_yesno("fb_is_16bpp")) {
		video_uc_priv->bpix = VIDEO_BPP16;
		priv->pixel_format = WIN_FMT_RGB565;
	} else {
		video_uc_priv->bpix = VIDEO_BPP32;
		priv->pixel_format = WIN_FMT_xRGB8888;
	}

	priv->win_num = lcdc_win_sel(LCDC_IN_LCD_AXI);
	video_set_flush_dcache(dev, true);

	sf_fb_lcdc_clk_cfg(priv);
	lcdc_config(priv);
	lcdc_run(priv, priv->win_num, LCDC_RUN);

	ret = display_enable(disp, 1 << video_uc_priv->bpix, &priv->timing);
	if (ret ) {
		dev_err(dev, "failed to enable display: %d\n", ret);
		return ret;
	}

	return 0;
}

static const struct udevice_id fwcon_ids[] = {
	{ .compatible = "starfive,fwcon" },
	{ }
};

static const struct video_ops fwcon_ops = {
};

U_BOOT_DRIVER(starfive_fwcon) = {
	.name		= "starfive-fwcon",
	.id		= UCLASS_VIDEO,
	.of_match = fwcon_ids,
	.ops		= &fwcon_ops,
	.bind		= fwcon_bind,
	.probe		= fwcon_probe,
	.priv_auto	= sizeof(struct fwcon_priv),
};
