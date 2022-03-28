/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:09:37 by maroly            #+#    #+#             */
/*   Updated: 2022/03/28 18:09:22 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"


int what_dir(t_gbl *gbl)
{
	if (gbl->rc->side == 0 && gbl->rc->rayDirX > 0)
		return (NO);
	else if (gbl->rc->side == 0 && gbl->rc->rayDirX <= 0)
		return (SO);
	else if (gbl->rc->side == 1 && gbl->rc->rayDirY > 0)
		return (EA);
	else if (gbl->rc->side == 1 && gbl->rc->rayDirY <= 0)
		return (WE);
	return (-1);
}

void	stripe_tex(t_gbl *gbl, int x)
{
	double wallX; //where exactly the wall was hit

	if(gbl->rc->side == 0)
		wallX = gbl->rc->posY + gbl->rc->perpWall * gbl->rc->rayDirY;
	else
		wallX = gbl->rc->posX + gbl->rc->perpWall * gbl->rc->rayDirX;
	// wallX -= floor((wallX));
	int what_tex = what_dir(gbl);
	//x coordinate on the texture
	int texX = (int)wallX * gbl->tex_tab[what_tex]->texWidth;
	if (gbl->rc->side == 0 && gbl->rc->rayDirX > 0)
		texX = gbl->tex_tab[what_tex]->texWidth - texX - 1;
	if (gbl->rc->side == 1 && gbl->rc->rayDirY < 0)
		texX = gbl->tex_tab[what_tex]->texWidth - texX - 1;

	// TODO: an integer-only bersenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * gbl->tex_tab[what_tex]->texHeight / gbl->rc->lineheight;
	// Starting texture coordinate
	double texPos = (gbl->rc->drawstart /*- pitch*/ - HEIGHT / 2 + gbl->rc->lineheight / 2) * step;
	for(int y = gbl->rc->drawstart; y < gbl->rc->drawend; y++)
	{
	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (gbl->tex_tab[what_tex]->texHeight - 1);
		texPos += step;
		unsigned int color = gbl->tex_tab[what_tex]->addr[texY * gbl->tex_tab[what_tex]->texHeight + texX];
	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(gbl->rc->side == 1) 
			color = (color >> 1) & 8355711;
		gbl->mlx->addr[y * WIDTH + x] = color;
	}
}

static void	trace_stripe(t_gbl *gbl, int x)
{
	//t_pos	beg;
	//t_pos	end;
	//int		color = 0x5F3384;

	if (gbl->rc->perpWall != 0)
		gbl->rc->lineheight = (int)(WALL_HEIGHT / gbl->rc->perpWall);
	else
		gbl->rc->lineheight = (int)WALL_HEIGHT;
	gbl->rc->drawstart = -gbl->rc->lineheight / 2 + WALL_HEIGHT / 2;
	if (gbl->rc->drawstart < 0)
		gbl->rc->drawstart = 0;
	gbl->rc->drawend = gbl->rc->lineheight / 2 + WALL_HEIGHT / 2; // + 100 regarde le ciel, -100 le sol
	if (gbl->rc->drawend >= WALL_HEIGHT)
		gbl->rc->drawend = WALL_HEIGHT - 1;
	stripe_tex(gbl, x);
	// if (rc->side == 1)
	// 	color = (color >> 1) & 8355711;
	// draw_line(beg, end, mlx, color);
	
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
	rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
	rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
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

void	floor_sky(t_gbl *gbl)
{
	int x;
	int y;
	double head;

	y = -1;
	head = 0.500000000000;
	while (++y < HEIGHT)
	{
		x = -1;
		if (y < HEIGHT * head)
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, 0xFF0515A1>>1);
		else
			while (++x < WIDTH)
				put_pixel_image(gbl->mlx, x, y, 0xFF0515A1);
	}
}

static void start(t_rc *rc, t_gbl *gbl)
{
	int	x;

	x = 0;
	floor_sky(gbl);
	while (x < WALL_WIDTH)
	{
		init_calcul(rc, x);//calcul side / Δ / cameraX / raydir
		trace_ray(rc, gbl);//trace les rayons jusqu'aux murs
		trace_stripe(gbl, x);//print stripe de X dans mxl_img
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

void    re_win(t_gbl *gbl)
{
	mlx_destroy_image(gbl->mlx->mlx, gbl->mlx->img);
	gbl->mlx->img = mlx_new_image(gbl->mlx->mlx, WIDTH, HEIGHT);
	gbl->mlx->addr = mlx_get_data_addr(gbl->mlx->img, &gbl->mlx->bpp,
			&gbl->mlx->line_length, &gbl->mlx->endian);
}

int	destroy_window(t_gbl *gbl)
{

	exit(end_free(gbl));
}

int	controls(int keycode, t_gbl *gbl)
{
	if (keycode == ESC)
		destroy_window(gbl);
	if (keycode == SHIFT)
	{
			if (gbl->rc->is_running == false)
			{
				gbl->rc->speed *= 1.6;
				gbl->rc->is_running = true;
			}
			else
			{
				gbl->rc->speed /= 1.6;
				gbl->rc->is_running = false;
			}
	}
	if (keycode == UP)
	{
		if (gbl->map[(int)(gbl->rc->posY + gbl->rc->dirY * gbl->rc->speed)][(int)gbl->rc->posX] != '1')
			gbl->rc->posY = gbl->rc->posY + gbl->rc->dirY * gbl->rc->speed;
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + gbl->rc->dirX * gbl->rc->speed)] != '1')
			gbl->rc->posX = gbl->rc->posX + gbl->rc->dirX * gbl->rc->speed;
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == DOWN)
	{
		if (gbl->map[(int)(gbl->rc->posY - gbl->rc->dirY * gbl->rc->speed)][(int)gbl->rc->posX] != '1')
			gbl->rc->posY = gbl->rc->posY - gbl->rc->dirY * gbl->rc->speed;
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX - gbl->rc->dirX * gbl->rc->speed)] != '1')
			gbl->rc->posX = gbl->rc->posX - gbl->rc->dirX * gbl->rc->speed;
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == LEFT)
	{
		if (gbl->map[(int)(gbl->rc->posY + (gbl->rc->dirX * sin(-PI / 2) + gbl->rc->dirY * cos(-PI / 2)) * (gbl->rc->speed / 2))][(int)gbl->rc->posX] != '1')
			gbl->rc->posY += ((gbl->rc->dirX * sin(-PI / 2) + gbl->rc->dirY * cos(-PI / 2)) * (gbl->rc->speed / 2));
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + (gbl->rc->dirX * cos(-PI / 2) - gbl->rc->dirY * sin(-PI / 2)) * (gbl->rc->speed / 2))] != '1')
			gbl->rc->posX += ((gbl->rc->dirX * cos(-PI / 2) - gbl->rc->dirY * sin(-PI / 2)) * (gbl->rc->speed / 2));
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == RIGHT)
	{
		if (gbl->map[(int)(gbl->rc->posY + (gbl->rc->dirX * sin(PI / 2) + gbl->rc->dirY * cos(PI / 2)) * (gbl->rc->speed / 2))][(int)gbl->rc->posX] != '1')
			gbl->rc->posY += ((gbl->rc->dirX * sin(PI / 2) + gbl->rc->dirY * cos(PI / 2)) * (gbl->rc->speed / 2));
		if (gbl->map[(int)gbl->rc->posY][(int)(gbl->rc->posX + (gbl->rc->dirX * cos(PI / 2) - gbl->rc->dirY * sin(PI / 2)) * (gbl->rc->speed / 2))] != '1')
			gbl->rc->posX += ((gbl->rc->dirX * cos(PI / 2) - gbl->rc->dirY * sin(PI / 2)) * (gbl->rc->speed / 2));
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == ARROW_LEFT)
	{
		double oldDirX = gbl->rc->dirX;
		gbl->rc->dirX = gbl->rc->dirX * cos(-0.03) - gbl->rc-> dirY * sin(-0.03);
		gbl->rc->dirY = oldDirX * sin(-0.03) + gbl->rc->dirY * cos(-0.03);
		double oldPlaneX = gbl->rc->planeX;
		gbl->rc->planeX = gbl->rc->planeX * cos(-0.03) - gbl->rc->planeY * sin(-0.03);
		gbl->rc->planeY = oldPlaneX * sin(-0.03) + gbl->rc->planeY * cos(-0.03);
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	else if (keycode == ARROW_RIGHT)
	{
		double oldDirX = gbl->rc->dirX;
		gbl->rc->dirX = gbl->rc->dirX * cos(0.03) - gbl->rc->dirY * sin(0.03);
		gbl->rc->dirY = oldDirX * sin(0.03) + gbl->rc->dirY * cos(0.03);
		double oldPlaneX = gbl->rc->planeX;
		gbl->rc->planeX = gbl->rc->planeX * cos(0.03) - gbl->rc->planeY * sin(0.03);
		gbl->rc->planeY = oldPlaneX * sin(0.03) + gbl->rc->planeY * cos(0.03);
		re_win(gbl);
		start(gbl->rc, gbl);
		mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	}
	return (1);
}

/*int	mouse(int x, int y, t_gbl *gbl)
{
	(void)y;

}*/

int ray_casting(t_gbl *gbl)
{
	t_rc rc;
	//int e, f;

	gbl->rc = &rc;
	if (!find_pos(gbl, &rc))
		return (0);
	init_dir(gbl, &rc);
	gbl->rc->speed = 0.15;
	gbl->rc->is_running = false;
	start(&rc, gbl);
	//	printf("%p\n", gbl->mlx->img);

	//printf("%d %d\n", e, f);
	mlx_put_image_to_window(gbl->mlx->mlx, gbl->mlx->mlx_win, gbl->mlx->img, 0, 0);
	mlx_hook(gbl->mlx->mlx_win, 2, 1L >> 0, controls, gbl);
	//mlx_hook(gbl->mlx->mlx_win, 6, 1L >> 0, mouse, gbl);
	mlx_hook(gbl->mlx->mlx_win, 17, 0, destroy_window, gbl);
	mlx_loop(gbl->mlx->mlx);
	return (1);
}