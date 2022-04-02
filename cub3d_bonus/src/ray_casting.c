/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/04/02 15:25:07 by maroly           ###   ########.fr       */
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
		if (gbl->map[rc->mapy][rc->mapx] == '2')
			if ((rc->side == 1 && rc->sidey > 2.5000)
				|| (rc->side == 0 && rc->sidex > 2.5000))
				rc->hit = 2;
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

void	print_cloud(t_gbl *gbl)
{
	int	x;
	int	y;
	char *tmp;
	unsigned int color;

	y = -1;
	while (++y < gbl->tex_tab[CL]->texheight)
	{
		x = -1;
		while (++x < gbl->tex_tab[CL]->texwidth)
		{
			tmp = gbl->tex_tab[CL]->addr + (y * gbl->tex_tab[CL]->line_length + x * (gbl->tex_tab[CL]->bpp / 8));
			color = *(unsigned int*)tmp;
			if (color != 4278190080 && color != 15599110)
				put_pixel_image(gbl->mlx, x + gbl->posxcloud, 50 + y + gbl->posycloud, color);
		}
	}
	gbl->posxcloud += 0.15;
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
		{
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, gbl->floor);
		}
	}
	print_cloud(gbl);
}

void	start(t_rc *rc, t_gbl *gbl)
{
	int	x;

	x = 0;
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
	start(gbl->rc, gbl);
	print_map(gbl);
	mlx_put_image_to_window(gbl->mlx->mlx,
		gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	//usleep(500000);
	return (1);
}
