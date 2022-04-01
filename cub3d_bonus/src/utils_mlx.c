/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:03:25 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 18:40:00 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	re_win(t_gbl *gbl)
{
	mlx_destroy_image(gbl->mlx->mlx, gbl->mlx->img);
	gbl->mlx->img = mlx_new_image(gbl->mlx->mlx, WIDTH, HEIGHT);
	gbl->mlx->addr = mlx_get_data_addr(gbl->mlx->img, &gbl->mlx->bpp,
			&gbl->mlx->line_length, &gbl->mlx->endian);
}

int	destroy_window(t_gbl *gbl)
{
	exit(end_free(gbl));
}

void	reframe(t_gbl *gbl)
{
	re_win(gbl);
	start(gbl->rc, gbl);
	print_map(gbl);
	mlx_put_image_to_window(gbl->mlx->mlx,
		gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
}
