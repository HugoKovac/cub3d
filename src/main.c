/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:22:18 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/30 14:40:26 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int main(int ac, char **av)
{
	t_gbl *gbl;
	t_mlx *mlx;

	if (ac != 2)
		return (1);
	gbl = malloc(sizeof(t_gbl));
	*gbl = (t_gbl){0};
	gbl->horizon = 0.500000000;
	mlx = malloc(sizeof(t_mlx));
	gbl->mlx = mlx;	
	parse_map(gbl, av[1]);
	open_texture(gbl);
	init_mlx(mlx, WIDTH, HEIGHT);
	if (!ray_casting(gbl))
	{
		end_free(gbl);
		return (1);
	}
	return (end_free(gbl));
}