/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_wasd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:52:46 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 18:56:16 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	shift(t_gbl *gbl)
{
	if (gbl->rc->is_running == false)
	{
		gbl->rc->speed *= 1.6;
		gbl->rc->is_running = true;
	}
	else
	{
		gbl->rc->speed /= 1.6;
		gbl->rc->is_running = false;
	}
}

void	up(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posy + gbl->rc->diry
			* gbl->rc->speed)][(int)gbl->rc->posx] != '1')
		gbl->rc->posy = gbl->rc->posy + gbl->rc->diry * gbl->rc->speed;
	if (gbl->map[(int)gbl->rc->posy][(int)(gbl->rc->posx + gbl->rc->dirx
		* gbl->rc->speed)] != '1')
		gbl->rc->posx = gbl->rc->posx + gbl->rc->dirx * gbl->rc->speed;
}

void	down(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posy - gbl->rc->diry
			* gbl->rc->speed)][(int)gbl->rc->posx] != '1')
		gbl->rc->posy = gbl->rc->posy - gbl->rc->diry * gbl->rc->speed;
	if (gbl->map[(int)gbl->rc->posy][(int)(gbl->rc->posx - gbl->rc->dirx
		* gbl->rc->speed)] != '1')
		gbl->rc->posx = gbl->rc->posx - gbl->rc->dirx * gbl->rc->speed;
}

void	left(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posy + (gbl->rc->dirx * sin(-PI / 2))
			* (gbl->rc->speed / 2))][(int)gbl->rc->posx] != '1')
		gbl->rc->posy += ((gbl->rc->dirx * sin(-PI / 2))
				* (gbl->rc->speed / 2));
	if (gbl->map[(int)gbl->rc->posy][(int)(gbl->rc->posx
		+ (-(gbl->rc->diry) * sin(-PI / 2)) * (gbl->rc->speed / 2))] != '1')
		gbl->rc->posx += ((-(gbl->rc->diry) * sin(-PI / 2))
				* (gbl->rc->speed / 2));
}

void	right(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posy + (gbl->rc->dirx * sin(PI / 2))
			* (gbl->rc->speed / 2))][(int)gbl->rc->posx] != '1')
		gbl->rc->posy += ((gbl->rc->dirx * sin(PI / 2)) * (gbl->rc->speed / 2));
	if (gbl->map[(int)gbl->rc->posy][(int)(gbl->rc->posx
		+ (-(gbl->rc->diry) * sin(PI / 2)) * (gbl->rc->speed / 2))] != '1')
		gbl->rc->posx += ((-(gbl->rc->diry) * sin(PI / 2))
				* (gbl->rc->speed / 2));
}
