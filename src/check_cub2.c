/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:12:55 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 17:40:20 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	is_j_in(char *str, int j)
{
	int size;

	size = ft_strlen(str);
	if (j < size)
		return (0);
	return (1);
}

int	max_len(t_gbl *gbl)
{
	int i;
	int compare;
	int max;

	i = -1;
	while (gbl->map[++i])
	{
		if (i == 0)
			max = ft_strlen(gbl->map[i]);
		else
		{
			compare = ft_strlen(gbl->map[i]);
			if (max < compare)
				max = compare;
		}
	}
	return (max);
}

int check_map_horizontal(t_gbl *gbl)
{
	int i;
	int j;

	i = -1;
	while (gbl->map[++i])
	{
		j = 0;
		while (gbl->map[i][j])
		{
			while (gbl->map[i][j] && gbl->map[i][j] == ' ')
				j++;
			if (!gbl->map[i][j])
				break;
			if (gbl->map[i][j] != '1')
				return (1);
			while (gbl->map[i][j] && gbl->map[i][j] != ' ')
			{
				if (check_char(gbl->map[i][j]) == 1)
					return (1);
				j++;
			}
			if (i > 0 && gbl->map[i][j - 1] && gbl->map[i][j - 1] != '1')
				return (1);
		}
	}
	return (0);
}

int check_map_vertical(t_gbl *gbl)
{
	int i;
	int j;
	int size;

	j = -1;
	i = 0;
	size = max_len(gbl);
	while (++j < size)
	{
		while (gbl->map[i])
		{
			while (gbl->map[i] && (is_j_in(gbl->map[i], j) == 1 || gbl->map[i][j] == ' '))
				i++;
			if (!gbl->map[i])
				break;
			if (is_j_in(gbl->map[i], j) == 0 && gbl->map[i][j] != '1')
				return (1);
			while (gbl->map[i] && is_j_in(gbl->map[i], j) == 0 && check_char(gbl->map[i][j]) == 0)
				i++;
			if (i > 0 && gbl->map[i - 1][j] != '1')
				return (1);
		}
		i = 0;
	}
	return (0);
}

int door_places(t_gbl *gbl)
{
	int x;
	int y;

	y = -1;
	while (gbl->map[++y])
	{
		x = -1;
		while (gbl->map[y][++x])
			if (gbl->map[y][x] == '2')
			{
				if ((gbl->map[y][x - 1] == '1' && gbl->map[y][x + 1] == '1') || (gbl->map[y - 1][x] == '1' && gbl->map[y + 1][x] == '1'))
					continue;
				else
					return (0);
			}
	}
	return (1);
}

void check_map_form(t_gbl *gbl)
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
		write(2, "Error\nBad door placement\n", ft_strlen("Error\nBad door placement\n"));
		err_exit(gbl);
	}
}