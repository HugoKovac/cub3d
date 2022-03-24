/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/03/24 16:20:45 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	trace_stripe(t_rc *rc, t_mlx *mlx, int x)
{
	t_pos beg;
	t_pos end;

	if (rc->perpWall != 0)
		rc->lineheight = (int)(WALL_HEIGHT / rc->perpWall);
	else
		rc->lineheight = (int)WALL_HEIGHT;
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
	int color = 0x5F3384;
	if (rc->side == 1)
		color /= 2;
	draw_line(beg, end, mlx, color);
	
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
	//if (rc->has_dir_changed == false)
	//{
		rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
		rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
	//}
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
	while (x < WALL_WIDTH)
	{
		init_calcul(rc, x);//calcul side / Δ / cameraX / raydir
		trace_ray(rc, gbl);//trace les rayons jusqu'aux murs
		trace_stripe(rc, gbl->mlx, x);//print stripe de X dans mxl_img
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
				rc->posX = (float)j + 0.5;
				rc->posY = (float)i + 0.5;
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

int	destroy_window(t_gbl *gbl)
{

	exit(end_free(gbl));
}

int	controls(int keycode, t_gbl *gbl)
{
	printf("test\n");
	if (keycode == ESC)
		destroy_window(gbl);
	else if (keycode == UP)
	{
		
	}
	else if (keycode == DOWN)
	{
		
	}
	else if (keycode == LEFT)
	{
		
	}
	else if (keycode == RIGHT)
	{
		
	}
	else if (keycode == ARROW_LEFT)
	{

		double oldDirX = gbl->rc->dirX;
		gbl->rc->dirX = gbl->rc->dirX * cos(0.1) - gbl->rc-> dirY * sin(0.1);
		gbl->rc->dirY = oldDirX * sin(0.1) + gbl->rc->dirY * cos(0.1);
		double oldPlaneX = gbl->rc->planeX;
		gbl->rc->planeX = gbl->rc->planeX * cos(0.1) - gbl->rc->planeY * sin(0.1);
		gbl->rc->planeY = oldPlaneX * sin(0.1) + gbl->rc->planeY * cos(0.1);
		//start(gbl->rc, gbl);
	}
	else if (keycode == ARROW_RIGHT)
	{
		double oldDirX = gbl->rc->dirX;
		gbl->rc->dirX = gbl->rc->dirX * cos(-0.1) - gbl->rc->dirY * sin(-0.1);
		gbl->rc->dirY = oldDirX * sin(-0.1) + gbl->rc->dirY * cos(-0.1);
		double oldPlaneX = gbl->rc->planeX;
		gbl->rc->planeX = gbl->rc->planeX * cos(-0.1) - gbl->rc->planeY * sin(-0.1);
		gbl->rc->planeY = oldPlaneX * sin(-0.1) + gbl->rc->planeY * cos(-0.1);
		//start(gbl->rc, gbl);
	}
	return (1);
}

int ray_casting(t_gbl *gbl)
{
	t_rc rc;

	gbl->rc = &rc;
	if (!find_pos(gbl, &rc))
		return (0);
	init_dir(gbl, &rc);
	start(&rc, gbl);
	mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	mlx_hook(gbl->mlx->mlx_win, 2, 0,controls, gbl);
	mlx_hook(gbl->mlx->mlx_win, 17, 0, destroy_window, gbl);
	return (1);
}