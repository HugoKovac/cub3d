/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:05:14 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 10:05:40 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	controls(int keycode, t_gbl *gbl)
{
	if (keycode == ESC)
		destroy_window(gbl);
	if (keycode == SHIFT)
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
	if (keycode == UP)
	{
		if (gbl->map[(int)(gbl->rc->posY + gbl->rc->dirY * gbl->rc->speed)][(int)gbl->rc->posX] != '1')
			gbl->rc->posY = gbl->rc->posY + gbl->rc->dirY * gbl->rc->speed;
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + gbl->rc->dirX * gbl->rc->speed)] != '1')
			gbl->rc->posX = gbl->rc->posX + gbl->rc->dirX * gbl->rc->speed;
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == DOWN)
	{
		if (gbl->map[(int)(gbl->rc->posY - gbl->rc->dirY * gbl->rc->speed)][(int)gbl->rc->posX] != '1')
			gbl->rc->posY = gbl->rc->posY - gbl->rc->dirY * gbl->rc->speed;
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX - gbl->rc->dirX * gbl->rc->speed)] != '1')
			gbl->rc->posX = gbl->rc->posX - gbl->rc->dirX * gbl->rc->speed;
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == LEFT)
	{
		if (gbl->map[(int)(gbl->rc->posY + (gbl->rc->dirX * sin(-PI / 2) + gbl->rc->dirY * cos(-PI / 2)) * (gbl->rc->speed / 2))][(int)gbl->rc->posX] != '1')
			gbl->rc->posY += ((gbl->rc->dirX * sin(-PI / 2) + gbl->rc->dirY * cos(-PI / 2)) * (gbl->rc->speed / 2));
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + (gbl->rc->dirX * cos(-PI / 2) - gbl->rc->dirY * sin(-PI / 2)) * (gbl->rc->speed / 2))] != '1')
			gbl->rc->posX += ((gbl->rc->dirX * cos(-PI / 2) - gbl->rc->dirY * sin(-PI / 2)) * (gbl->rc->speed / 2));
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == RIGHT)
	{
		if (gbl->map[(int)(gbl->rc->posY + (gbl->rc->dirX * sin(PI / 2) + gbl->rc->dirY * cos(PI / 2)) * (gbl->rc->speed / 2))][(int)gbl->rc->posX] != '1')
			gbl->rc->posY += ((gbl->rc->dirX * sin(PI / 2) + gbl->rc->dirY * cos(PI / 2)) * (gbl->rc->speed / 2));
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + (gbl->rc->dirX * cos(PI / 2) - gbl->rc->dirY * sin(PI / 2)) * (gbl->rc->speed / 2))] != '1')
			gbl->rc->posX += ((gbl->rc->dirX * cos(PI / 2) - gbl->rc->dirY * sin(PI / 2)) * (gbl->rc->speed / 2));
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == ARROW_LEFT)
	{
		double oldDirX = gbl->rc->dirX;
		gbl->rc->dirX = gbl->rc->dirX * cos(-0.03) - gbl->rc-> dirY * sin(-0.03);
		gbl->rc->dirY = oldDirX * sin(-0.03) + gbl->rc->dirY * cos(-0.03);
		double oldPlaneX = gbl->rc->planeX;
		gbl->rc->planeX = gbl->rc->planeX * cos(-0.03) - gbl->rc->planeY * sin(-0.03);
		gbl->rc->planeY = oldPlaneX * sin(-0.03) + gbl->rc->planeY * cos(-0.03);
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == ARROW_RIGHT)
	{
		double oldDirX = gbl->rc->dirX;
		gbl->rc->dirX = gbl->rc->dirX * cos(0.03) - gbl->rc->dirY * sin(0.03);
		gbl->rc->dirY = oldDirX * sin(0.03) + gbl->rc->dirY * cos(0.03);
		double oldPlaneX = gbl->rc->planeX;
		gbl->rc->planeX = gbl->rc->planeX * cos(0.03) - gbl->rc->planeY * sin(0.03);
		gbl->rc->planeY = oldPlaneX * sin(0.03) + gbl->rc->planeY * cos(0.03);
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	return (1);
}
