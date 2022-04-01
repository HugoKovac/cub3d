/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:49:20 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 19:10:54 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	check_map_char(t_gbl *gbl)
{
	int	player;
	int	i;
	int	j;

	i = -1;
	player = 0;
	while (gbl->map[++i])
	{
		j = -1;
		while (gbl->map[i][++j])
			if (gbl->map[i][j] == 'N' || gbl->map[i][j] == 'E'
				|| gbl->map[i][j] == 'S' || gbl->map[i][j] == 'W')
				player++;
	}
	if (player != 1)
	{
		write(2, "Error\nWrong number of player\n",
			ft_strlen("Error\nWrong number of player\n"));
		err_exit(gbl);
	}
}

void	check_map_form(t_gbl *gbl)
{
	if (check_map_horizontal(gbl) == 1)
	{
		write(2, "Error\nMap not closed\n", ft_strlen("Error\nMap not closed\n"));
		err_exit(gbl);
	}
	if (check_map_vertical(gbl) == 1)
	{
		write(2, "Error\nMap not closed\n", ft_strlen("Error\nMap not closed\n"));
		err_exit(gbl);
	}
	if (count_island(gbl) > 1)
	{
		write(2, "Error\nToo many island\n", ft_strlen("Error\nToo many island\n"));
		err_exit(gbl);
	}
	if (door_places(gbl) == 0)
	{
		write(2, "Error\nBad door placement\n",
			ft_strlen("Error\nBad door placement\n"));
		err_exit(gbl);
	}
}

int	check_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != '2')
		return (1);
	return (0);
}
