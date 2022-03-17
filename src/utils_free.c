/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:48:50 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/17 16:17:04 by maroly           ###   ########.fr       */
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
	if (gbl->file)
		destroy_tab(gbl->file);
	if (gbl->no)
		free(gbl->no);
	if (gbl->so)
		free(gbl->so);
	if (gbl->we)
		free(gbl->we);
	if (gbl->ea)
		free(gbl->ea);
	if (gbl->f)
		free(gbl->f);
	if (gbl->c)
		free(gbl->c);
	free(gbl);
	return (0);
}	