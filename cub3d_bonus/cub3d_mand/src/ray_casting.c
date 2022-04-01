/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/04/01 12:35:58 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	trace_ray(t_rc *rc, t_gbl *gbl)
{
	while (rc->hit == 0)
	{
		if (rc->sidex < rc->sidey)
		{
			rc->sidex += rc->deltax;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidey += rc->deltay;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (gbl->map[rc->mapy][rc->mapx] == '1')
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpwall = rc->sidex - rc->deltax;
	else
		rc->perpwall = rc->sidey - rc->deltay;
}

unsigned int	rgb_file(char *str, t_gbl *gbl)
{
	char			**tab;
	char			*tmp;
	unsigned int	color;

	tab = ft_split(str, ',', gbl);
	tmp = malloc(sizeof(unsigned int));
	if (!tmp)
		err_exit(gbl);
	tmp[0] = ft_atoi(tab[0]);
	tmp[1] = ft_atoi(tab[1]);
	tmp[2] = ft_atoi(tab[2]);
	color = *(unsigned int *)tmp;
	free(tmp);
	destroy_tab(tab);
	return (color);
}

void	floor_sky(t_gbl *gbl)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		if (y < HEIGHT * gbl->horizon)
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, gbl->sky);
		else
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, gbl->floor);
	}
}

void	start(t_rc *rc, t_gbl *gbl)
{
	int	x;

	x = 0;
	gbl->count_tour++;
	floor_sky(gbl);
	while (x < WIDTH)
	{
		init_calcul(rc, x);
		trace_ray(rc, gbl);
		trace_stripe(gbl, x);
		x++;
	}
}

int	ray_casting(t_gbl *gbl)
{
	t_rc	rc;

	gbl->rc = &rc;
	if (!find_pos(gbl, &rc))
		return (0);
	init_dir(gbl, &rc);
	gbl->rc->speed = 0.15;
	gbl->rc->is_running = false;
	start(&rc, gbl);
	mlx_put_image_to_window(gbl->mlx->mlx,
		gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	mlx_hook(gbl->mlx->mlx_win, 2, 1L >> 0, controls, gbl);
	mlx_hook(gbl->mlx->mlx_win, 17, 0, destroy_window, gbl);
	mlx_loop(gbl->mlx->mlx);
	return (1);
}
