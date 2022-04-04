/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:52:01 by maroly            #+#    #+#             */
/*   Updated: 2022/04/04 11:52:16 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <include.h>

void	print_cloud(t_gbl *gbl)
{
	int				x;
	int				y;
	char			*tmp;
	unsigned int	color;

	y = -1;
	while (++y < gbl->tex_tab[CL]->texheight)
	{
		x = -1;
		while (++x < gbl->tex_tab[CL]->texwidth)
		{
			tmp = gbl->tex_tab[CL]->addr + (y * gbl->tex_tab[CL]->line_length
					+ x * (gbl->tex_tab[CL]->bpp / 8));
			color = *(unsigned int *)tmp;
			if (color != 4278190080 && color != 15599110)
				put_pixel_image(gbl->mlx, x + gbl->posxcloud,
					50 + y + gbl->posycloud, color);
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
