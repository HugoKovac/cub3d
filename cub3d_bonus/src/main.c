/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:22:18 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/02 14:39:52 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int ac, char **av)
{
	t_gbl	*gbl;
	t_mlx	*mlx;
	t_rc	rc;

	if (ac != 2)
		return (1);
	gbl = malloc(sizeof(t_gbl));
	*gbl = (t_gbl){0};
	gbl->horizon = 0.500000000;
	mlx = malloc(sizeof(t_mlx));
	*mlx = (t_mlx){0};
	gbl->mlx = mlx;
	parse_map(gbl, av[1]);
	open_texture(gbl);
	init_mlx(mlx, WIDTH, HEIGHT);
	gbl->rc = &rc;
	if (!find_pos(gbl, &rc))
		return (0);
	init_dir(gbl, &rc);
	gbl->rc->speed = 0.15;
	gbl->rc->is_running = false;
	mlx_hook(gbl->mlx->mlx_win, 2, 1L >> 0, controls, gbl);
	mlx_mouse_hook(gbl->mlx->mlx_win, mouse_pressed, gbl);
	mlx_hook(gbl->mlx->mlx_win, 6, 1 << 6, mouse, gbl);
	mlx_hook(gbl->mlx->mlx_win, 17, 0, destroy_window, gbl);
	mlx_loop_hook(mlx->mlx, ray_casting, gbl);
	mlx_loop(gbl->mlx->mlx);
	if (!ray_casting(gbl))
	{
		end_free(gbl);
		return (1);
	}
	return (end_free(gbl));
}
