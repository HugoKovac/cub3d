/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:58:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/17 17:24:38 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	all_param2(t_gbl *gbl, int i)
{
	if (gbl->file[i][0] == '\0')
		return ;
	else if (ft_strncmp("NO ", gbl->file[i], 3) == 0)
		gbl->no = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("SO ", gbl->file[i], 3) == 0)
		gbl->so = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("WE ", gbl->file[i], 3) == 0)
		gbl->we = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("EA ", gbl->file[i], 3) == 0)
		gbl->ea = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("F ", gbl->file[i], 2) == 0)
		gbl->f = ft_strdup(gbl->file[i] + 2);
	else if (ft_strncmp("C ", gbl->file[i], 2) == 0)
		gbl->c = ft_strdup(gbl->file[i] + 2);
	else
	{
		write (1, "Error\n", 6);
		err_exit(gbl);
	}
}

void	all_param(t_gbl *gbl)
{
	int		i;

	i = -1;
	while (gbl->file[++i] && &gbl->file[i] != gbl->map)
		all_param2(gbl, i);
	if (!gbl->no || !gbl->so || !gbl->we
		|| !gbl->ea || !gbl->f || !gbl->c)
	{
		write (1, "Error\n", 6);
		err_exit(gbl);
	}
}

int	check_char(char c)
{
	if (c != '0' || c != '1' || c != 'N' || c != 'S' || c != 'E' || c != 'W')
		return (0);
	return (1);
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
			if (gbl->map[i][j] != '1')
				return (1);
			while (gbl->map[i][++j] && gbl->map[i][j] != ' ')
				if (check_char(gbl->map[i][j]) == 1)
					return (1);
			if (gbl->map[i][j - 1] != '1')
				return (1);
			if (gbl->map[i][j])
				j++;
		}
	}
	return (0);
}

int	is_j_sup(char *str, int j)
{
	int size;

	size = ft_strlen(str);
	if (j < size)
		return (0);
	return (1);
}

int check_map_vertical(t_gbl *gbl)
{
	int i;
	int j;

	j = -1;
	i = 0;
	while (gbl->map[i][++j])
	{
		while (gbl->map[i])
		{
			while (gbl->map[i] && is_j_sup(gbl->map[i], j) == 0 && gbl->map[i][j] == ' ')
				i++;
			if (gbl->map[i] && is_j_sup(gbl->map[i], j) == 0 && gbl->map[i][j] != '1')
				return (1);
			while (gbl->map[i] && is_j_sup(gbl->map[i], j) == 0 && gbl->map[i][j] != ' ')
				i++;
			if (i > 0 && gbl->map[i - 1] && is_j_sup(gbl->map[i - 1], j) == 0
				&& gbl->map[i - 1][j] != '1' && gbl->map[i - 1][j] != ' ')
				return (1);
			if (gbl->map[i])
				i++;
		}
		i = 0;
	}
	return (0);
}

void check_map_form(t_gbl *gbl)
{
	if (check_map_horizontal(gbl) == 1)
	{
		write(2, "Error\n", 6);
		err_exit(gbl);
	}
	if (check_map_vertical(gbl) == 1)
	{
		write(2, "Error\n", 6);
		err_exit(gbl);
	}
}
