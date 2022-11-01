// SPDX-License-Identifier: GPL-2.0

#include "starfive-clkgen.h"
#include <dm.h>

static ulong starfive_clkgen_fdiv_get_rate(struct clk *clk)
{
	int ret;
	u32 reg;
	u32 div100;
	ulong parent_rate;

	assert(ID_IS_VALID(clk->id));

	reg = starfive_clkgen_reg_get(clk);
	ret = starfive_clkgen_get_parent_rate(clk, &parent_rate);
	if (ret != 0) {
		return ret;
	}

	div100 = 100 * (reg & JH7100_CLK_INT_MASK) +
		((reg & JH7100_CLK_FRAC_MASK) >> JH7100_CLK_FRAC_SHIFT);

	return (div100 >= JH7100_CLK_FRAC_MIN) ? 100 * parent_rate / div100 : 0;
}

static ulong starfive_clkgen_fdiv_set_rate(struct clk *clk,
					   ulong rate)
{
	return -EINVAL;
}

static ulong starfive_clkgen_fdiv_round_rate(struct clk *clk,
					     ulong rate)
{
	return -EINVAL;
}

struct clk_ops starfive_clkgen_fdiv_ops = {
	.round_rate = starfive_clkgen_fdiv_round_rate,
	.set_rate = starfive_clkgen_fdiv_set_rate,
	.get_rate = starfive_clkgen_fdiv_get_rate,
};
