/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:58:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/18 14:54:27 by maroly           ###   ########.fr       */
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
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

void	check_map_char(t_gbl *gbl)
{
	int player;
	int i;
	int j;

	i = -1;
	player = 0;
	while (gbl->map[++i])
	{
		j = -1;
		while (gbl->map[i][++j])
			if (gbl->map[i][j] == 'N')
				player++;
	}
	if (player != 1)
	{
		write(2, "Error\n", 6);
		err_exit(gbl);
	}
}
