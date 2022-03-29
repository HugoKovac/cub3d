/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:58:38 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 10:00:10 by hkovac           ###   ########.fr       */
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

void	trace_stripe(t_gbl *gbl, int x)
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