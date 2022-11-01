// SPDX-License-Identifier: GPL-2.0

#include "starfive-clkgen.h"
#include <dm.h>

static ulong starfive_clkgen_fixed_get_rate(struct clk *clk)
{
	int ret;
	ulong parent_rate;

	assert(ID_IS_VALID(clk->id));

	ret = starfive_clkgen_get_parent_rate(clk, &parent_rate);
	if (ret != 0) {
		return ret;
	}

	return parent_rate;
}

static ulong starfive_clkgen_synth_get_rate(struct clk *clk)
{
	int ret;
	ulong parent_rate;
	const struct jh7100_clk_data *clk_data;

	assert(ID_IS_VALID(clk->id));

	clk_data = &jh7100_clk_data[clk->id];
	assert((clk_data->flags & CLF_SYNTH) != 0);

	ret = starfive_clkgen_get_parent_rate(clk, &parent_rate);
	if (ret != 0) {
		return ret;
	}

	return parent_rate * clk_data->max;
}

static ulong starfive_clkgen_fixed_set_rate(struct clk *clk,
					    ulong rate)
{
	/*
	 * TBD: Set parent rate here, but only if CLF_SET_RATE_PARENT is set.
	 */

	return -EINVAL;
}

struct clk_ops starfive_clkgen_gate_ops = {
	.enable = starfive_clkgen_common_enable,
	.disable = starfive_clkgen_common_disable,
	.get_rate = starfive_clkgen_fixed_get_rate,
	.set_rate = starfive_clkgen_fixed_set_rate,
};

struct clk_ops starfive_clkgen_gmux_ops = {
	.set_parent = starfive_clkgen_common_set_parent,
	.enable = starfive_clkgen_common_enable,
	.disable = starfive_clkgen_common_disable,
	.get_rate = starfive_clkgen_fixed_get_rate,
	.set_rate = starfive_clkgen_fixed_set_rate,
};

struct clk_ops starfive_clkgen_mux_ops = {
	.set_parent = starfive_clkgen_common_set_parent,
	.get_rate = starfive_clkgen_fixed_get_rate,
	.set_rate = starfive_clkgen_fixed_set_rate,
};

struct clk_ops starfive_clkgen_inv_ops = {
	.get_rate = starfive_clkgen_fixed_get_rate,
	.set_rate = starfive_clkgen_fixed_set_rate,
};

struct clk_ops starfive_clkgen_synth_ops = {
	.get_rate = starfive_clkgen_synth_get_rate,
};
