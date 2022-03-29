/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/03/29 21:00:02 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void trace_ray(t_rc *rc, t_gbl *gbl)
{
	while (rc->hit == 0)
	{
		if(rc->sideX < rc->sideY)
		{
			rc->sideX += rc->deltaX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
		  rc->sideY += rc->deltaY;
		  rc->mapY += rc->stepY;
		  rc->side = 1;
		}
		if(gbl->map[rc->mapY][rc->mapX] == '1')
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpWall = rc->sideX - rc->deltaX;
	else
		rc->perpWall = rc->sideY - rc->deltaY;
}

static void	find_side(t_rc *rc)
{
	if(rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideX = (rc->posX - rc->mapX) * rc->deltaX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideX = (rc->mapX + 1.0 - rc->posX) * rc->deltaX;
	}
	if(rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideY = (rc->posY - rc->mapY) * rc->deltaY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideY = (rc->mapY + 1.0 - rc->posY) * rc->deltaY;
	}
}

static void init_calcul(t_rc *rc, int x)
{
	rc->hit = 0;
	rc->cameraX = 2 * x / (double)WALL_WIDTH - 1;
	rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
	rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
	rc->mapX = (int)rc->posX;
	rc->mapY = (int)rc->posY;
	if (rc->rayDirX == 0)
		rc->deltaX = 1e30;
	else
		rc->deltaX = fabs(1 / rc->rayDirX);
	if (rc->rayDirY == 0)
		rc->deltaY = 1e30;
	else
		rc->deltaY = fabs(1 / rc->rayDirY);
	find_side(rc);
}

unsigned int	rgb_file(char *str, t_gbl *gbl)
{
	char			**tab;
	char	*tmp;
	unsigned int	color;

	tab = ft_split(str, ',', gbl);
	tmp = malloc(sizeof(unsigned int));
	if (!tmp)
		err_exit(gbl);
	tmp[0] = ft_atoi(tab[0], gbl);
	tmp[1] = ft_atoi(tab[1], gbl);
	tmp[2] = ft_atoi(tab[2], gbl);
	color = *(unsigned int*)tmp;
	free(tmp);
	destroy_tab(tab);
	return (color);
}

void	floor_sky(t_gbl *gbl)
{
	int x;
	int y;
	double head;

	y = -1;
	head = 0.500000000000;
	printf("%d %d\n", gbl->sky, gbl->floor);
	while (++y < HEIGHT)
	{
		x = -1;
		if (y < HEIGHT * head)
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, gbl->sky);
		else
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, gbl->floor);
	}
}

void start(t_rc *rc, t_gbl *gbl)
{
	int	x;

	x = 0;
	floor_sky(gbl);
	while (x < WIDTH)
	{
		init_calcul(rc, x);//calcul side / Δ / cameraX / raydir
		trace_ray(rc, gbl);//trace les rayons jusqu'aux murs
		trace_stripe(gbl, x);//print stripe de X dans mxl_img
		x++;
	}
}

int ray_casting(t_gbl *gbl)
{
	t_rc rc;

	gbl->rc = &rc;
	if (!find_pos(gbl, &rc))
		return (0);
	init_dir(gbl, &rc);
	gbl->rc->speed = 0.15;
	gbl->rc->is_running = false;
	start(&rc, gbl);
	mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	mlx_hook(gbl->mlx->mlx_win, 2, 1L >> 0, controls, gbl);
	//mlx_hook(gbl->mlx->mlx_win, 6, 1L >> 0, mouse, gbl);
	mlx_hook(gbl->mlx->mlx_win, 17, 0, destroy_window, gbl);
	mlx_loop(gbl->mlx->mlx);
	return (1);
}