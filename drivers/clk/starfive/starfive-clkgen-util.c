// SPDX-License-Identifier: GPL-2.0

#include "starfive-clkgen.h"
#include <dm.h>

void jh7100_clk_reg_rmw(struct clk *clk,
                        u32 mask,
                        u32 value)
{
	struct jh7100_clk_priv *priv = dev_get_priv(clk->dev);
	void *reg = priv->base + 4 * clk->id;

	value |= readl(reg) & ~mask;
	writel(value, reg);
}

u32 starfive_clkgen_reg_get(struct clk *clk)
{
	struct jh7100_clk_priv *priv = dev_get_priv(clk->dev);

	return readl(priv->base + 4 * clk->id);
}

const char *starfive_clkgen_name(struct clk *clk)
{
	const struct jh7100_clk_data *clk_data;

	assert(ID_IS_VALID(clk->id));

	clk_data = &jh7100_clk_data[clk->id];
	return clk_data->name;
}

int starfive_clkgen_get_parent(struct clk *clk,
			       struct clk *parent)
{
	u32 reg;
	u8 parent_id;
	struct clk parent_clk;
	const struct jh7100_clk_data *clk_data;
	const struct jh7100_clk_data *parent_clk_data;
	struct jh7100_clk_priv *priv = dev_get_priv(clk->dev);
	int err = 0;

	assert(ID_IS_VALID(clk->id));

	clk_data = &jh7100_clk_data[clk->id];
	reg = starfive_clkgen_reg_get(clk);

	parent_id = clk_data->parents[REG_2_PARENT_IDX(reg)];
	if (ID_IS_VALID(parent_id)) {
		parent_clk_data = &jh7100_clk_data[parent_id];
		parent_clk = *clk;
		parent_clk.rate = 0;
		parent_clk.id = parent_id;
	} else {
		switch (parent_id) {
		case JH7100_CLK_OSC_SYS:
			parent_clk = priv->parent_sys;
			break;
		case JH7100_CLK_OSC_AUD:
			parent_clk = priv->parent_aud;
			break;
		default:
			err = -ENOENT;
		}
	}

	if (err != 0) {
		return err;
	}

	*parent = parent_clk;
	return 0;
}

int starfive_clkgen_get_parent_rate(struct clk *clk,
				    ulong *rate)
{
	int ret;
	struct clk parent_clk;

	ret = starfive_clkgen_get_parent(clk, &parent_clk);
	if (ret != 0) {
		return ret;
	}

	*rate = clk_get_rate(&parent_clk);
	return 0;
}
