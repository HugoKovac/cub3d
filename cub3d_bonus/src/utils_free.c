/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:48:50 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/04 13:04:21 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	destroy_tex_mlx(t_mlx **tex_tab)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		mlx_destroy_image(tex_tab[i]->mlx, tex_tab[i]->img);
		mlx_destroy_display(tex_tab[i]->mlx);
		free(tex_tab[i]->mlx);
		free(tex_tab[i]);
	}
	free(tex_tab);
}

void	destroy_mlx(t_mlx *mlx)
{
	if (mlx->mlx && mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx && mlx->mlx_win)
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	if (mlx->mlx)
		free(mlx->mlx);
	free(mlx);
}

void	destroy_tab(char **tab)
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

void	destroy_tex(char *tab[8])
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (tab[i])
			free(tab[i]);
	}
}

int	end_free(t_gbl *gbl)
{
	if (gbl->file)
		destroy_tab(gbl->file);
	destroy_tex(gbl->tex_string);
	if (gbl->tex_tab)
		destroy_tex_mlx(gbl->tex_tab);
	if (gbl->mlx)
		destroy_mlx(gbl->mlx);
	free(gbl);
	return (0);
}
