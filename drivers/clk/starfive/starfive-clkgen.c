// SPDX-License-Identifier: GPL-2.0

#include "starfive-clkgen.h"
#include <dm.h>

static struct clk_ops *starfive_clkgen_get_ops(struct clk *clk)
{
	const struct jh7100_clk_data *clk_data;

	assert(ID_IS_VALID(clk->id));

	clk_data = &jh7100_clk_data[clk->id];
	if ((clk_data->flags & CLF_DIV) != 0) {
		if ((clk_data->flags & CLF_MUXED) != 0) {
			if ((clk_data->flags & CLF_GATED) != 0) {

				return &starfive_clkgen_gmd_ops;
			}

			return &starfive_clkgen_mdiv_ops;
		}

		if ((clk_data->flags & CLF_GATED) != 0) {
			return &starfive_clkgen_gdiv_ops;
		}

		if ((clk_data->flags & CLF_FRAC) != 0) {
			return &starfive_clkgen_fdiv_ops;
		}

		return &starfive_clkgen_div_ops;
	}

	if ((clk_data->flags & CLF_MUXED) != 0) {
		if ((clk_data->flags & CLF_GATED) != 0) {
			return &starfive_clkgen_gmux_ops;
		}

		return &starfive_clkgen_mux_ops;
	}

	if ((clk_data->flags & CLF_GATED) != 0) {
		return &starfive_clkgen_gate_ops;
	}

	if ((clk_data->flags & CLF_INVERT) != 0) {
		return &starfive_clkgen_inv_ops;
	}

	if ((clk_data->flags & CLF_SYNTH) != 0) {
		return &starfive_clkgen_synth_ops;
	}

	pr_err("%s for %s: no ops\n", __FUNCTION__, starfive_clkgen_name(clk));
	return NULL;
}

static ulong starfive_clkgen_round_rate(struct clk *clk,
					ulong rate)
{
	struct clk_ops *real_ops;

	if (!ID_IS_VALID(clk->id)) {
		return -EINVAL;
	}

	real_ops = starfive_clkgen_get_ops(clk);
	if (real_ops == NULL || real_ops->round_rate == NULL) {
		return -EINVAL;
	}

	return real_ops->round_rate(clk, rate);
}

static int starfive_clkgen_set_parent(struct clk *clk,
				      struct clk *parent)
{
	struct clk_ops *real_ops;

	if (!ID_IS_VALID(clk->id)) {
		return -EINVAL;
	}

	real_ops = starfive_clkgen_get_ops(clk);
	if (real_ops == NULL || real_ops->set_parent == NULL) {
		return -EINVAL;
	}

	return real_ops->set_parent(clk, parent);
}

static ulong starfive_clkgen_get_rate(struct clk *clk)
{
	struct clk_ops *real_ops;

	if (!ID_IS_VALID(clk->id)) {
		return -EINVAL;
	}

	real_ops = starfive_clkgen_get_ops(clk);
	if (real_ops == NULL || real_ops->get_rate == NULL) {
		return -EINVAL;
	}

	return real_ops->get_rate(clk);
}

static ulong starfive_clkgen_set_rate(struct clk *clk, ulong rate)
{
	struct clk_ops *real_ops;

	if (!ID_IS_VALID(clk->id)) {
		return -EINVAL;
	}

	real_ops = starfive_clkgen_get_ops(clk);
	if (real_ops == NULL || real_ops->set_rate == NULL) {
		return -EINVAL;
	}

	return real_ops->set_rate(clk, rate);
}

static int starfive_clkgen_enable(struct clk *clk)
{
	struct clk_ops *real_ops;

	if (!ID_IS_VALID(clk->id)) {
		return -EINVAL;
	}

	real_ops = starfive_clkgen_get_ops(clk);
	if (real_ops == NULL || real_ops->enable == NULL) {
		return -EINVAL;
	}

	return real_ops->enable(clk);
}

static int starfive_clkgen_disable(struct clk *clk)
{
	struct clk_ops *real_ops;

	if (!ID_IS_VALID(clk->id)) {
		return -EINVAL;
	}

	real_ops = starfive_clkgen_get_ops(clk);
	if (real_ops == NULL || real_ops->disable == NULL) {
		return -EINVAL;
	}

	return real_ops->disable(clk);
}

static int starfive_clkgen_probe(struct udevice *dev)
{
	int err;
	struct jh7100_clk_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base) {
		return -EINVAL;
	}

	err = clk_get_by_name(dev, "osc_sys", &priv->parent_sys);
	if (err) {
		return err;
	}

	err = clk_get_by_name(dev, "osc_aud", &priv->parent_aud);
	if (err) {
		return err;
	}

	return 0;
}

static struct clk_ops starfive_clkgen_ops = {
	.set_parent = starfive_clkgen_set_parent,
	.round_rate = starfive_clkgen_round_rate,
	.set_rate = starfive_clkgen_set_rate,
	.get_rate = starfive_clkgen_get_rate,
	.enable = starfive_clkgen_enable,
	.disable = starfive_clkgen_disable,
};

static const struct udevice_id starfive_clkgen_ids[] = {
	{ .compatible = "starfive,jh7100-clkgen" },
	{ }
};

U_BOOT_DRIVER(starfive_clkgen) = {
	.name = DRIVER_NAME,
	.id = UCLASS_CLK,
	.of_match = starfive_clkgen_ids,
	.probe = starfive_clkgen_probe,
	.ops = &starfive_clkgen_ops,
	.priv_auto = sizeof(struct jh7100_clk_priv),
};
