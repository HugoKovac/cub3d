/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/03/22 17:53:05 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	trace_stripe(t_rc *rc, t_gbl *gbl)
{
	rc->lineheight = (int)(HEIGHT / rc->perpWall);
	rc->drawstart = -rc->lineheight / 2 + HEIGHT / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + HEIGHT / 2;
	if (rc->drawend >= HEIGHT)
		rc->drawend = HEIGHT - 1;
	
}

static void trace_ray(t_rc *rc, t_gbl *gbl)
{
	while (rc->hit == 0)
	{
		if(rc->sideX < rc->sideY)
		{
			rc->sideX += rc->deltaX;
			rc->mapX += rc->stepX;
			rc->side = 0;
        }
        else
        {
          rc->sideY += rc->deltaY;
          rc->mapY += rc->stepY;
          rc->side = 1;
        }
        if(gbl->map[rc->mapX][rc->mapY] > 0)
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpWall = rc->sideX - rc->deltaX;
	else
		rc->perpWall = rc->sideY - rc->deltaY;
}

static void	find_side(t_rc *rc, t_gbl *gbl)
{
	if(rc->rayDirX < 0)
	{
	rc->stepX = -1;
	rc->sideX = (rc->posX - rc->mapX) * rc->deltaX;
	}
	else
	{
	rc->stepX = 1;
	rc->sideX = (rc->mapX + 1.0 - rc->posX) * rc->deltaX;
	}
	if(rc->rayDirY < 0)
	{
	rc->stepY = -1;
	rc->sideY = (rc->posY - rc->mapY) * rc->deltaY;
	}
	else
	{
	rc->stepY = 1;
	rc->sideY = (rc->mapY + 1.0 - rc->posY) * rc->deltaY;
	}
}

static void init_calcul(t_rc *rc, t_gbl *gbl, int x)
{
	rc->hit = 0;
	rc->cameraX = 2 * x / (double)WIDTH - 1;
	rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
	rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
	rc->mapX = (int)rc->posX;//arrondir?
	rc->mapY = (int)rc->posY;
	if (rc->rayDirX == 0)
		rc->deltaX = 1e30;
	else
		rc->deltaX = abs(1 / rc->rayDirX);
	if (rc->rayDirY == 0)
		rc->deltaY = 1e30;
	else
    	rc->deltaY = abs(1 / rc->rayDirY);
	find_side(rc, gbl);
}

static void calcul_camera_x(t_rc *rc, t_gbl *gbl)
{
	int	x;

	x = 0;
	rc->planeX = 0;
	rc->planeY = 0.66;
	while (x < WIDTH)
	{
		init_calcul(rc, gbl, x);//calcul side / Δ / cameraX / raydir
		trace_ray(rc, gbl);
		trace_stripe(rc, gbl);
	}
}

int ray_casting(t_gbl *gbl)
{
	t_rc rc;
	int	done;

	done = 0;
	while (done == 0)
	{
		calcul_camera_x(&rc, gbl);//calcul de tout le champ de vision
	}
	return (0);
}