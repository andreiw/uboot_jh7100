// SPDX-License-Identifier: GPL-2.0

#include "starfive-clkgen.h"
#include <dm.h>

int starfive_clkgen_common_enable(struct clk *clk)
{
	assert(ID_IS_VALID(clk->id));

	jh7100_clk_reg_rmw(clk, JH7100_CLK_ENABLE, JH7100_CLK_ENABLE);

	if ((starfive_clkgen_reg_get(clk) & JH7100_CLK_ENABLE) != 0) {
		return 0;
	}

	return -ENXIO;
}

int starfive_clkgen_common_disable(struct clk *clk)
{
	assert(ID_IS_VALID(clk->id));

	jh7100_clk_reg_rmw(clk, JH7100_CLK_ENABLE, 0);

	if ((starfive_clkgen_reg_get(clk) & JH7100_CLK_ENABLE) == 0) {
		return 0;
	}

	return -ENXIO;
}

int starfive_clkgen_common_set_parent(struct clk *clk,
				      struct clk *parent)
{
	assert(ID_IS_VALID(clk->id));

	return -EINVAL;
}
