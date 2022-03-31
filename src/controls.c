/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:05:14 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 02:40:49 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	head_up(t_gbl *gbl, int mult)
{
	gbl->head += 10 * mult;
	gbl->horizon += 0.0156 * mult;
}

void	head_down(t_gbl *gbl, int mult)
{
	gbl->head -= 10 * mult;
	gbl->horizon -= 0.0156 * mult;
}

void	up(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posY + gbl->rc->dirY * gbl->rc->speed)][(int)gbl->rc->posX] != '1')
		gbl->rc->posY = gbl->rc->posY + gbl->rc->dirY * gbl->rc->speed;
	if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + gbl->rc->dirX * gbl->rc->speed)] != '1')
		gbl->rc->posX = gbl->rc->posX + gbl->rc->dirX * gbl->rc->speed;
}

void	down(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posY - gbl->rc->dirY * gbl->rc->speed)][(int)gbl->rc->posX] != '1')
		gbl->rc->posY = gbl->rc->posY - gbl->rc->dirY * gbl->rc->speed;
	if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX - gbl->rc->dirX * gbl->rc->speed)] != '1')
		gbl->rc->posX = gbl->rc->posX - gbl->rc->dirX * gbl->rc->speed;
}

void left(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posY + (gbl->rc->dirX * sin(-PI / 2)) * (gbl->rc->speed / 2))][(int)gbl->rc->posX] != '1')
		gbl->rc->posY += ((gbl->rc->dirX * sin(-PI / 2)) * (gbl->rc->speed / 2));
	if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + (- gbl->rc->dirY * sin(-PI / 2)) * (gbl->rc->speed / 2))] != '1')
		gbl->rc->posX += ((- gbl->rc->dirY * sin(-PI / 2)) * (gbl->rc->speed / 2));
}

void	right(t_gbl *gbl)
{
	if (gbl->map[(int)(gbl->rc->posY + (gbl->rc->dirX * sin(PI / 2)) * (gbl->rc->speed / 2))][(int)gbl->rc->posX] != '1')
		gbl->rc->posY += ((gbl->rc->dirX * sin(PI / 2)) * (gbl->rc->speed / 2));
	if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + (- gbl->rc->dirY * sin(PI / 2)) * (gbl->rc->speed / 2))] != '1')
		gbl->rc->posX += ((- gbl->rc->dirY * sin(PI / 2)) * (gbl->rc->speed / 2));
}

void	arrow_left(t_gbl *gbl, int mult)
{
	double oldDirX = gbl->rc->dirX;
	gbl->rc->dirX = gbl->rc->dirX * cos(-0.03 * mult) - gbl->rc-> dirY * sin(-0.03 * mult);
	gbl->rc->dirY = oldDirX * sin(-0.03 * mult) + gbl->rc->dirY * cos(-0.03 * mult);
	double oldPlaneX = gbl->rc->planeX;
	gbl->rc->planeX = gbl->rc->planeX * cos(-0.03 * mult) - gbl->rc->planeY * sin(-0.03 * mult);
	gbl->rc->planeY = oldPlaneX * sin(-0.03 * mult) + gbl->rc->planeY * cos(-0.03 * mult);
}

void	arrow_right(t_gbl *gbl, int mult)
{
	double oldDirX = gbl->rc->dirX;
	gbl->rc->dirX = gbl->rc->dirX * cos(0.03 * mult) - gbl->rc->dirY * sin(0.03 * mult);
	gbl->rc->dirY = oldDirX * sin(0.03 * mult) + gbl->rc->dirY * cos(0.03 * mult);
	double oldPlaneX = gbl->rc->planeX;
	gbl->rc->planeX = gbl->rc->planeX * cos(0.03 * mult) - gbl->rc->planeY * sin(0.03 * mult);
	gbl->rc->planeY = oldPlaneX * sin(0.03 * mult) + gbl->rc->planeY * cos(0.03 * mult);
}

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

int	controls(int keycode, t_gbl *gbl)
{
	if (keycode == ESC)
		destroy_window(gbl);
	if (keycode == SHIFT)
		shift(gbl);
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
	else if (keycode == ARROW_UP)
		head_up(gbl, 1);
	else if (keycode == ARROW_DOWN)
		head_down(gbl, 1);
	reframe(gbl);
	return (1);
}
