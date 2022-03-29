/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:03:25 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 10:04:50 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void    re_win(t_gbl *gbl)
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
