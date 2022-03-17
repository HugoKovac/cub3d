/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:58:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/17 11:43:25 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	all_param2(t_gbl *gbl, int i)
{
	if (gbl->map[i][0] == '\0')
		return ;
	else if (ft_strncmp("NO ", gbl->map[i], 3) == 0)
		gbl->no = ft_strdup(gbl->map[i] + 3);
	else if (ft_strncmp("SO ", gbl->map[i], 3) == 0)
		gbl->so = ft_strdup(gbl->map[i] + 3);
	else if (ft_strncmp("WE ", gbl->map[i], 3) == 0)
		gbl->we = ft_strdup(gbl->map[i] + 3);
	else if (ft_strncmp("EA ", gbl->map[i], 3) == 0)
		gbl->ea = ft_strdup(gbl->map[i] + 3);
	else if (ft_strncmp("F ", gbl->map[i], 2) == 0)
		gbl->f = ft_strdup(gbl->map[i] + 2);
	else if (ft_strncmp("C ", gbl->map[i], 2) == 0)
		gbl->c = ft_strdup(gbl->map[i] + 2);
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
	while (gbl->map[++i])
		all_param2(gbl, i);
	if (!gbl->no || !gbl->so || !gbl->we
		|| !gbl->ea || !gbl->f || !gbl->c)
	{
		write (1, "Error\n", 6);
		err_exit(gbl);
	}
}

void	check_map_head(t_gbl *gbl)
{
	all_param(gbl);
}
// check_map_form();