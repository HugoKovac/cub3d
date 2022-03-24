/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:44:08 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 10:32:36 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	err_exit(t_gbl *gbl)
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
	close_tex(gbl->tex);
	if (gbl->tex)
		free(gbl->tex);
	//free_mlx();//a faire
	free(gbl);
	exit (1);
}
