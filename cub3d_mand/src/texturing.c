/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:58:38 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/01 12:28:51 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	what_dir(t_gbl *gbl)
{
	if (gbl->rc->side == 0 && gbl->rc->raydirx > 0)
		return (NO);
	else if (gbl->rc->side == 0 && gbl->rc->raydirx <= 0)
		return (SO);
	else if (gbl->rc->side == 1 && gbl->rc->raydiry > 0)
		return (EA);
	else if (gbl->rc->side == 1 && gbl->rc->raydiry <= 0)
		return (WE);
	return (-1);
}

void	stripe_tex2(t_gbl *gbl, t_tex *st)
{
	if (gbl->rc->side == 0)
		st->wallx = gbl->rc->posy + gbl->rc->perpwall * gbl->rc->raydiry;
	else
		st->wallx = gbl->rc->posx + gbl->rc->perpwall * gbl->rc->raydirx;
	st->wallx -= floor(st->wallx);
	st->what_tex = what_dir(gbl);
	st->texx = (int)(st->wallx * (double)gbl->tex_tab[st->what_tex]->texwidth);
	if (gbl->rc->side == 0 && gbl->rc->raydirx > 0)
		st->texx = gbl->tex_tab[st->what_tex]->texwidth - st->texx - 1;
	if (gbl->rc->side == 1 && gbl->rc->raydiry < 0)
		st->texx = gbl->tex_tab[st->what_tex]->texwidth - st->texx - 1;
	st->step = 1.0 * gbl->tex_tab[st->what_tex]
		->texheight / gbl->rc->lineheight;
	st->texpos = (gbl->rc->drawstart - gbl->head - HEIGHT / 2
			+ gbl->rc->lineheight / 2) * st->step;
}

void	stripe_tex(t_gbl *gbl, int x)
{
	t_tex			st;
	int				y;

	stripe_tex2(gbl, &st);
	y = gbl->rc->drawstart;
	while (y < gbl->rc->drawend)
	{
		st.texy = (int)st.texpos & (gbl->tex_tab[st.what_tex]->texheight - 1);
		st.texpos += st.step;
		st.tmp = gbl->tex_tab[st.what_tex]->addr
			+ (st.texy * gbl->tex_tab[st.what_tex]
				->line_length + st.texx * (gbl->tex_tab[st.what_tex]->bpp / 8));
		st.color = *(unsigned int *)st.tmp;
		if (gbl->rc->side == 1)
			st.color = (st.color >> 1) & 8355711;
		put_pixel_image(gbl->mlx, x, y, st.color);
		y++;
	}
}

void	trace_stripe(t_gbl *gbl, int x)
{
	if (gbl->rc->perpwall != 0)
		gbl->rc->lineheight = (int)(HEIGHT / gbl->rc->perpwall);
	else
		gbl->rc->lineheight = (int)HEIGHT;
	gbl->rc->drawstart = -gbl->rc->lineheight / 2 + HEIGHT / 2 + gbl->head;
	if (gbl->rc->drawstart < 0)
		gbl->rc->drawstart = 0;
	gbl->rc->drawend = gbl->rc->lineheight / 2 + HEIGHT / 2 + gbl->head;
	if (gbl->rc->drawend >= HEIGHT)
		gbl->rc->drawend = HEIGHT - 1;
	stripe_tex(gbl, x);
}
