// SPDX-License-Identifier: GPL-2.0

#include "starfive-clkgen.h"
#include <dm.h>

static ulong starfive_clkgen_div_get_rate(struct clk *clk)
{
	int ret;
	u32 reg;
	u32 div;
	ulong parent_rate;

	assert(ID_IS_VALID(clk->id));

	reg = starfive_clkgen_reg_get(clk);
	ret = starfive_clkgen_get_parent_rate(clk, &parent_rate);
	if (ret != 0) {
		return ret;
	}

	div = reg & JH7100_CLK_DIV_MASK;
	return div ? parent_rate / div : 0;
}

static ulong starfive_clkgen_div_set_rate(struct clk *clk,
					  ulong rate)
{
	return -EINVAL;
}

static ulong starfive_clkgen_div_round_rate(struct clk *clk,
					    ulong rate)
{
	return -EINVAL;
}

struct clk_ops starfive_clkgen_gmd_ops = {
	.set_parent = starfive_clkgen_common_set_parent,
	.round_rate = starfive_clkgen_div_round_rate,
	.set_rate = starfive_clkgen_div_set_rate,
	.get_rate = starfive_clkgen_div_get_rate,
	.enable = starfive_clkgen_common_enable,
	.disable = starfive_clkgen_common_disable,
};

struct clk_ops starfive_clkgen_mdiv_ops = {
	.set_parent = starfive_clkgen_common_set_parent,
	.round_rate = starfive_clkgen_div_round_rate,
	.set_rate = starfive_clkgen_div_set_rate,
	.get_rate = starfive_clkgen_div_get_rate,
};

struct clk_ops starfive_clkgen_gdiv_ops = {
	.round_rate = starfive_clkgen_div_round_rate,
	.set_rate = starfive_clkgen_div_set_rate,
	.get_rate = starfive_clkgen_div_get_rate,
	.enable = starfive_clkgen_common_enable,
	.disable = starfive_clkgen_common_disable,
};

struct clk_ops starfive_clkgen_div_ops = {
	.round_rate = starfive_clkgen_div_round_rate,
	.set_rate = starfive_clkgen_div_set_rate,
	.get_rate = starfive_clkgen_div_get_rate,
};
