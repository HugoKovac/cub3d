/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:44:08 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 02:10:17 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	err_exit(t_gbl *gbl)
{
	if (gbl->file)
		destroy_tab(gbl->file);
	//if (gbl->tex_string)
		destroy_tex(gbl->tex_string);
	if (gbl->tex_tab)
		destroy_tex_mlx(gbl->tex_tab);
	if (gbl->mlx)
		destroy_mlx(gbl->mlx);
	free(gbl);
	exit (1);
}
