/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_handv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:22:57 by maroly            #+#    #+#             */
/*   Updated: 2022/04/02 21:26:48 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	check_map_horizontal2(t_gbl *gbl, int *i, int *j)
{
	while (gbl->map[*i][*j] && gbl->map[*i][*j] == ' ')
		(*j)++;
	if (!gbl->map[*i][*j])
		return (2);
	if (gbl->map[*i][*j] != '1')
		return (1);
	while (gbl->map[*i][*j] && gbl->map[*i][*j] != ' ')
	{
		if (check_char(gbl->map[*i][*j]) == 1)
			return (1);
		(*j)++;
	}
	if (*i > 0 && gbl->map[*i][(*j) - 1] && gbl->map[*i][(*j) - 1] != '1')
		return (1);
	return (0);
}

int	check_map_horizontal(t_gbl *gbl)
{
	int	i;
	int	j;
	int	rtn;

	i = -1;
	while (gbl->map[++i])
	{
		j = 0;
		while (gbl->map[i][j])
		{
			rtn = check_map_horizontal2(gbl, &i, &j);
			if (rtn == 1)
				return (1);
			else if (rtn == 2)
				break ;
		}
	}
	return (0);
}

int	check_map_vertical2(t_gbl *gbl, int *j)
{
	int i;

	i = 0;
	while (gbl->map[i])
	{
		while (gbl->map[i] && (is_j_in(gbl->map[i], *j) == 1
				|| gbl->map[i][*j] == ' '))
			i++;
		if (!gbl->map[i])
			break;
		if (is_j_in(gbl->map[i], *j) == 0 && gbl->map[i][*j] != '1')
			return (1);
		while (gbl->map[i] && is_j_in(gbl->map[i], *j) == 0
			&& check_char(gbl->map[i][*j]) == 0)
			i++;
		if (i > 0 && gbl->map[(i) - 1][*j] != '1')
			return (1);
	}
	return (0);
}

int	check_map_vertical(t_gbl *gbl)
{
	int	j;
	int	size;

	j = -1;
	size = max_len(gbl);
	while (++j < size)
		if (check_map_vertical2(gbl, &j) != 0)
			return (1);
	return (0);
}
