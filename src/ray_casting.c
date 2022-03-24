/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/03/24 09:52:59 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	trace_stripe(t_rc *rc, t_mlx *mlx, int x)
{
	t_pos beg;
	t_pos end;

	rc->lineheight = (int)(WALL_HEIGHT / rc->perpWall);
	rc->drawstart = -rc->lineheight / 2 + WALL_HEIGHT / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + WALL_HEIGHT / 2;
	if (rc->drawend >= WALL_HEIGHT)
		rc->drawend = WALL_HEIGHT - 1;
	beg.x = x;
	beg.y = rc->drawstart;
	end.x = x;
	end.y = rc->drawend;
	draw_line(beg, end, mlx);
	
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
        if(gbl->map[rc->mapY][rc->mapX] == '1')
			rc->hit = 1;
	}
	//printf("%f | %f\n", rc->sideX, rc->sideY);
	if (rc->side == 0)
		rc->perpWall = rc->sideX - rc->deltaX;
	else
		rc->perpWall = rc->sideY - rc->deltaY;
}

static void	find_side(t_rc *rc)
{
	if(rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideX = (rc->posX - rc->mapX) * rc->deltaX;
	}
	else
	{
		// printf("%d %f %f\n", rc->mapX, rc->posX, rc->deltaX);
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

static void init_calcul(t_rc *rc, int x)
{
	rc->hit = 0;
	rc->cameraX = 2 * x / (double)WALL_WIDTH - 1;
	rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
	rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
	printf("X : %f		Y : %f\n", rc->rayDirX, rc->rayDirY);
	rc->mapX = (int)rc->posX;//arrondir?
	rc->mapY = (int)rc->posY;//arrondir?
	if (rc->rayDirX == 0)
		rc->deltaX = 1e30;
	else
		rc->deltaX = fabs(1 / rc->rayDirX);
	if (rc->rayDirY == 0)
		rc->deltaY = 1e30;
	else
    	rc->deltaY = fabs(1 / rc->rayDirY);
	find_side(rc);
}

static void start(t_rc *rc, t_gbl *gbl)
{
	int	x;

	x = 0;
	rc->planeX = 0;
	rc->planeY = 0.66;
	while (x < WALL_WIDTH)
	{
		init_calcul(rc, x);//calcul side / Δ / cameraX / raydir
		trace_ray(rc, gbl);//trace les rayons jusqu'aux murs
		trace_stripe(rc, gbl->mlx, x);//print srtripe de X dans mxl_img
		x++;
	}
}

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
				rc->posX = (float)j;
				rc->posY = (float)i;
				return (1);
			}
		}
	}
	return (0);
}

static void init_dir(t_gbl *gbl, t_rc *rc)
{
	if (gbl->map[(int)rc->posY][(int)rc->posX] == 'N')
	{
		rc->dirX = 0;
		rc->dirY = -1;
	}
	else if (gbl->map[(int)rc->posY][(int)rc->posX] == 'S')
	{
		rc->dirX = 0;
		rc->dirY = 1;
	}
	else if (gbl->map[(int)rc->posY][(int)rc->posX] == 'E')
	{
		rc->dirX = 1;
		rc->dirY = 0;
	}
	else// W
	{
		rc->dirX = -1;
		rc->dirY = 0;
	}
}

int ray_casting(t_gbl *gbl)
{
	t_rc rc;
	int	done;

	done = 0;
	// rc.posX = 2;
	// rc.posY = 2;
	if (!find_pos(gbl, &rc))
		return (0);
	init_dir(gbl, &rc);
	while (done == 0)// a enlever avec mlx loop ?
	{
		start(&rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	return (1);
}