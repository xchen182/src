/* $NetBSD: imx_ccm_gate.c,v 1.1 2020/01/15 01:09:57 jmcneill Exp $ */

/*-
 * Copyright (c) 2020 Jared McNeill <jmcneill@invisible.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: imx_ccm_gate.c,v 1.1 2020/01/15 01:09:57 jmcneill Exp $");

#include <sys/param.h>
#include <sys/bus.h>

#include <dev/clk/clk_backend.h>

#include <arm/imx/fdt/imx_ccm.h>

int
imx_ccm_gate_enable(struct imx_ccm_softc *sc, struct imx_ccm_clk *clk,
    int enable)
{
	struct imx_ccm_gate *gate = &clk->u.gate;
	uint32_t val;

	KASSERT(clk->type == IMX_CCM_GATE);

	val = CCM_READ(sc, gate->reg);
	if (enable)
		val |= gate->mask;
	else
		val &= ~gate->mask;
	CCM_WRITE(sc, gate->reg, val);

	return 0;
}

const char *
imx_ccm_gate_get_parent(struct imx_ccm_softc *sc,
    struct imx_ccm_clk *clk)
{
	struct imx_ccm_gate *gate = &clk->u.gate;

	KASSERT(clk->type == IMX_CCM_GATE);

	return gate->parent;
}
