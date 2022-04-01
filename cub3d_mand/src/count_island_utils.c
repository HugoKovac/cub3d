/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_island_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:58:38 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 18:58:57 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	free_tab(bool **tab, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

int	ft_biglen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	**init_map(t_gbl *gbl)
{
	bool	**map;
	int		i;
	int		size;

	i = -1;
	size = ft_biglen(gbl->map);
	map = malloc(sizeof(*map) * size);
	if (!map)
		err_exit(gbl);
	while (gbl->map[++i])
	{
		size = ft_strlen(gbl->map[i]);
		map[i] = malloc(sizeof(char *) * size);
		if (!map[i])
		{
			free_tab(map, i);
			err_exit(gbl);
		}
		ft_memset(map[i], 0, size);
	}
	return (map);
}
