/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:12:55 by maroly            #+#    #+#             */
/*   Updated: 2022/04/01 12:30:48 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	is_j_in(char *str, int j)
{
	int	size;

	size = ft_strlen(str);
	if (j < size)
		return (0);
	return (1);
}

int	max_len(t_gbl *gbl)
{
	int	i;
	int	compare;
	int	max;

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
