/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:22:18 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 09:08:10 by hkovac           ###   ########.fr       */
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
	mlx = malloc(sizeof(t_mlx));
	gbl->mlx = mlx;
	init_mlx(mlx, 860, 640);
	parse_map(gbl, av[1]);
	if (ray_casting(gbl))
	{
		// mlx_loop();
		end_free(gbl);
		return (1);
	}
	return (end_free(gbl));
}