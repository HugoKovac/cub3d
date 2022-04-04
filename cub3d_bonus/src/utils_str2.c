/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:42:39 by maroly            #+#    #+#             */
/*   Updated: 2022/04/04 14:00:29 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	check_rgb(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = -1;
		while (tab[i][++j])
			if (!(tab[i][j] >= '0' && tab[i][j] <= '9'))
				return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}
