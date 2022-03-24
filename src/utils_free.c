/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:48:50 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 15:14:38 by hkovac           ###   ########.fr       */
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

void	close_tex(t_tex *tex)
{
	if (tex->fd_NO > -1)
		close (tex->fd_NO);
	if (tex->fd_SO > -1)
		close (tex->fd_SO);
	if (tex->fd_WE > -1)
		close (tex->fd_WE);
	if (tex->fd_EA > -1)
		close (tex->fd_EA);
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
	if (gbl->tex)
	{
		close_tex(gbl->tex);
		free(gbl->tex);
	}		
	//free_mlx();//a faire
	free(gbl);
	return (0);
}	