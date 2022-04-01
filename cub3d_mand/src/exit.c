/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:44:08 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 18:25:34 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	err_exit(t_gbl *gbl)
{
	if (gbl->file)
		destroy_tab(gbl->file);
	destroy_tex(gbl->tex_string);
	if (gbl->tex_tab)
		destroy_tex_mlx(gbl->tex_tab);
	if (gbl->mlx)
		destroy_mlx(gbl->mlx);
	free(gbl);
	exit (1);
}
