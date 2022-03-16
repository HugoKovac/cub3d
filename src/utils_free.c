/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:48:50 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/16 16:09:36 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void destroy_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			if (tab[i])
				free(tab[i]);
		free(tab);
	}
	tab = NULL;
}

int	end_free(t_gbl *gbl)
{
	if (gbl->map)
		destroy_tab(gbl->map);
	return (0);
}	