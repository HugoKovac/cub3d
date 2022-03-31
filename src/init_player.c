/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:01:33 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 19:33:35 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	find_pos(t_gbl *gbl, t_rc *rc)
{
	int	i;
	int	j;

	i = -1;
	while (gbl->map[++i])
	{
		j = -1;
		while (gbl->map[i][++j])
		{
			if (gbl->map[i][j] == 'N' || gbl->map[i][j] == 'S'
				|| gbl->map[i][j] == 'W' || gbl->map[i][j] == 'E')
			{
				rc->posx = (float)j + 0.5;
				rc->posy = (float)i + 0.5;
				return (1);
			}
		}
	}
	return (0);
}

int	init_dir2(t_gbl *gbl, t_rc *rc)
{
	if (gbl->map[(int)rc->posy][(int)rc->posx] == 'N')
	{
		rc->dirx = 0.0;
		rc->diry = -1.0;
		rc->planex = 0.66;
		rc->planey = 0.0;
		return (1);
	}
	else if (gbl->map[(int)rc->posy][(int)rc->posx] == 'S')
	{
		rc->dirx = 0.0;
		rc->diry = 1.0;
		rc->planex = -0.66;
		rc->planey = 0.0;
		return (1);
	}
	else
		return (0);
}

void	init_dir(t_gbl *gbl, t_rc *rc)
{
	if (!init_dir2(gbl, rc))
	{	
		if (gbl->map[(int)rc->posy][(int)rc->posx] == 'E')
		{
			rc->dirx = 1.0;
			rc->diry = 0.0;
			rc->planex = 0.0;
			rc->planey = 0.66;
		}
		else
		{
			rc->dirx = -1.0;
			rc->diry = 0.0;
			rc->planex = 0.0;
			rc->planey = -0.66;
		}
	}
}
