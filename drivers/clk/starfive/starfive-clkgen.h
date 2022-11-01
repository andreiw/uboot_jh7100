// SPDX-License-Identifier: GPL-2.0

#pragma once

#include <common.h>
#include <clk-uclass.h>
#include <clk.h>
#include <dm/devres.h>
#include <dm/device_compat.h>
#include <reset.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/math64.h>
#include <linux/clk-provider.h>
#include <dt-bindings/clock/starfive-jh7100.h>

#define DRIVER_NAME "starfive-clkgen"

/* register fields */
#define JH7100_CLK_ENABLE	BIT(31)
#define JH7100_CLK_INVERT	BIT(30)
#define JH7100_CLK_MUX_MASK	GENMASK(27, 24)
#define JH7100_CLK_MUX_SHIFT	24
#define JH7100_CLK_DIV_MASK	GENMASK(23, 0)
#define JH7100_CLK_FRAC_MASK	GENMASK(15, 8)
#define JH7100_CLK_FRAC_SHIFT	8
#define JH7100_CLK_INT_MASK	GENMASK(7, 0)

#define REG_2_PARENT_IDX(x) (((x) & JH7100_CLK_MUX_MASK) >> JH7100_CLK_MUX_SHIFT)

#define ID_IS_VALID(x) ((x) < JH7100_CLK_END)

/* fractional divider min/max */
#define JH7100_CLK_FRAC_MIN	100UL
#define JH7100_CLK_FRAC_MAX	25599UL

/* external clocks */
#define JH7100_CLK_OSC_SYS		(JH7100_CLK_END + 0)
#define JH7100_CLK_OSC_AUD		(JH7100_CLK_END + 1)
#define JH7100_CLK_GMAC_RMII_REF	(JH7100_CLK_END + 2)
#define JH7100_CLK_GMAC_GR_MII_RX	(JH7100_CLK_END + 3)

struct jh7100_clk_priv {
	void __iomem *base;
	struct clk parent_sys;
	struct clk parent_aud;
};

struct jh7100_clk_data {
	const char *name;
#define CLF_DIV             BIT(0)
#define CLF_GATED           BIT(1)
#define CLF_MUXED           BIT(2)
#define CLF_FRAC            BIT(3)
#define CLF_INVERT          BIT(4)
#define CLF_SET_RATE_PARENT BIT(5)
#define CLF_CRITICAL        BIT(6)
#define CLF_SYNTH           BIT(7)
	unsigned long flags;
	u32 max;
	u8 parents[4];
};

struct jh7100_clk {
	unsigned int idx;
	unsigned int max_div;
};

extern const struct jh7100_clk_data jh7100_clk_data[];
extern struct clk_ops starfive_clkgen_gmd_ops;
extern struct clk_ops starfive_clkgen_mdiv_ops;
extern struct clk_ops starfive_clkgen_gdiv_ops;
extern struct clk_ops starfive_clkgen_fdiv_ops;
extern struct clk_ops starfive_clkgen_div_ops;
extern struct clk_ops starfive_clkgen_gmux_ops;
extern struct clk_ops starfive_clkgen_mux_ops;
extern struct clk_ops starfive_clkgen_gate_ops;
extern struct clk_ops starfive_clkgen_inv_ops;
extern struct clk_ops starfive_clkgen_synth_ops;

u32 starfive_clkgen_reg_get(struct clk *clk);
const char *starfive_clkgen_name(struct clk *clk);
int starfive_clkgen_get_parent(struct clk *clk, struct clk *parent);
int starfive_clkgen_get_parent_rate(struct clk *clk, ulong *rate);
int starfive_clkgen_common_enable(struct clk *clk);
int starfive_clkgen_common_disable(struct clk *clk);
int starfive_clkgen_common_set_parent(struct clk *clk, struct clk *parent);
void jh7100_clk_reg_rmw(struct clk *clk, u32 mask, u32 value);
