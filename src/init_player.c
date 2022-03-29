/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:01:33 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 10:02:11 by hkovac           ###   ########.fr       */
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
			if (gbl->map[i][j] == 'N' || gbl->map[i][j] == 'S' ||gbl->map[i][j] == 'W' ||gbl->map[i][j] == 'E')
			{
				rc->posX = (float)j + 0.5;
				rc->posY = (float)i + 0.5;
				return (1);
			}
		}
	}
	return (0);
}

void init_dir(t_gbl *gbl, t_rc *rc)
{

	if (gbl->map[(int)rc->posY][(int)rc->posX] == 'N')
	{
		rc->dirX = 0.0;
		rc->dirY = -1.0;
		rc->planeX = 0.66;
		rc->planeY = 0.0;
	}
	else if (gbl->map[(int)rc->posY][(int)rc->posX] == 'S')
	{
		rc->dirX = 0.0;
		rc->dirY = 1.0;
		rc->planeX = -0.66;
		rc->planeY = 0.0;
	}
	else if (gbl->map[(int)rc->posY][(int)rc->posX] == 'E')
	{
		rc->dirX = 1.0;
		rc->dirY = 0.0;
		rc->planeX = 0.0;
		rc->planeY = 0.66;
	}
	else// W
	{
		rc->dirX = -1.0;
		rc->dirY = 0.0;
		rc->planeX = 0.0;
		rc->planeY = -0.66;
	}
}