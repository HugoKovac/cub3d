/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_island.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:20:08 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 18:58:50 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

bool	is_in(bool **map, int i, int j, t_gbl *gbl)
{
	if (i > 0 && is_j_in(gbl->map[i - 1], j) == 0 && map[i - 1][j] == true)
		return (true);
	else if (j > 0 && map[i][j - 1] == true)
		return (true);
	else if (gbl->map[i + 1] && is_j_in(gbl->map[i + 1], j) == 0
		&& map[i + 1][j] == true)
		return (true);
	else if (gbl->map[i][j + 1] && map[i][j + 1] == true)
		return (true);
	return (false);
}

void	find_island(bool **map, t_gbl *gbl)
{
	int	i;
	int	j;
	int	col;
	int	row;

	i = -1;
	row = ft_biglen(gbl->map);
	while (++i < row)
	{
		j = -1;
		col = ft_strlen(gbl->map[i]);
		while (++j < col)
			if (gbl->map[i][j] != ' ' && map[i][j] == false
				&& is_in(map, i, j, gbl) == true)
				map[i][j] = true;
		if (col > 0)
			while (--col >= 0)
				if (gbl->map[i][col] != ' ' && map[i][col] == false
					&& is_in(map, i, col, gbl) == true)
					map[i][col] = true;
	}
}

int	count_island(t_gbl *gbl)
{
	bool		**map;
	int			i;
	int			j;
	t_island	island;

	i = -1;
	island.count = 0;
	island.row = ft_biglen(gbl->map);
	map = init_map(gbl);
	while (++i < island.row)
	{
		j = -1;
		island.col = ft_strlen(gbl->map[i]);
		while (++j < island.col)
		{
			if (gbl->map[i][j] != ' ' && map[i][j] == false)
			{
				map[i][j] = true;
				find_island(map, gbl);
				island.count++;
			}
		}
	}
	free_tab(map, island.row);
	return (island.count);
}
