/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:04:33 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 19:06:38 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	find_side(t_rc *rc)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidex = (rc->posx - rc->mapx) * rc->deltax;
	}
	else
	{
		rc->stepx = 1;
		rc->sidex = (rc->mapx + 1.0 - rc->posx) * rc->deltax;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidey = (rc->posy - rc->mapy) * rc->deltay;
	}
	else
	{
		rc->stepy = 1;
		rc->sidey = (rc->mapy + 1.0 - rc->posy) * rc->deltay;
	}
}

void	init_calcul(t_rc *rc, int x)
{
	rc->hit = 0;
	rc->camerax = 2 * x / (double)WIDTH - 1;
	rc->raydirx = rc->dirx + rc->planex * rc->camerax;
	rc->raydiry = rc->diry + rc->planey * rc->camerax;
	rc->mapx = (int)rc->posx;
	rc->mapy = (int)rc->posy;
	if (rc->raydirx == 0)
		rc->deltax = 1e30;
	else
		rc->deltax = fabs(1 / rc->raydirx);
	if (rc->raydiry == 0)
		rc->deltay = 1e30;
	else
		rc->deltay = fabs(1 / rc->raydiry);
	find_side(rc);
}
