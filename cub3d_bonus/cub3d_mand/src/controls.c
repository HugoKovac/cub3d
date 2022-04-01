/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:05:14 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/01 12:34:25 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	arrow_left(t_gbl *gbl, int mult)
{
	double	olddirx;
	double	oldplanex;

	olddirx = gbl->rc->dirx;
	gbl->rc->dirx = gbl->rc->dirx * cos(-0.03 * mult)
		- gbl->rc-> diry * sin(-0.03 * mult);
	gbl->rc->diry = olddirx * sin(-0.03 * mult)
		+ gbl->rc->diry * cos(-0.03 * mult);
	oldplanex = gbl->rc->planex;
	gbl->rc->planex = gbl->rc->planex * cos(-0.03 * mult)
		- gbl->rc->planey * sin(-0.03 * mult);
	gbl->rc->planey = oldplanex * sin(-0.03 * mult)
		+ gbl->rc->planey * cos(-0.03 * mult);
}

void	arrow_right(t_gbl *gbl, int mult)
{
	double	olddirx;
	double	oldplanex;

	olddirx = gbl->rc->dirx;
	gbl->rc->dirx = gbl->rc->dirx * cos(0.03 * mult)
		- gbl->rc->diry * sin(0.03 * mult);
	gbl->rc->diry = olddirx * sin(0.03 * mult)
		+ gbl->rc->diry * cos(0.03 * mult);
	oldplanex = gbl->rc->planex;
	gbl->rc->planex = gbl->rc->planex * cos(0.03 * mult)
		- gbl->rc->planey * sin(0.03 * mult);
	gbl->rc->planey = oldplanex * sin(0.03 * mult)
		+ gbl->rc->planey * cos(0.03 * mult);
}

int	controls(int keycode, t_gbl *gbl)
{
	if (keycode == ESC)
		destroy_window(gbl);
	if (keycode == UP)
		up(gbl);
	else if (keycode == DOWN)
		down(gbl);
	else if (keycode == LEFT)
		left(gbl);
	else if (keycode == RIGHT)
		right(gbl);
	else if (keycode == ARROW_LEFT)
		arrow_left(gbl, 1);
	else if (keycode == ARROW_RIGHT)
		arrow_right(gbl, 1);
	reframe(gbl);
	return (1);
}
