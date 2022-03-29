/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:58:38 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 17:35:14 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef int int32;
typedef unsigned int Uint32;

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
	double	wallX;
	char	*tmp;
	unsigned int	color;

	if(gbl->rc->side == 0)
		wallX = gbl->rc->posY + gbl->rc->perpWall * gbl->rc->rayDirY;
	else
		wallX = gbl->rc->posX + gbl->rc->perpWall * gbl->rc->rayDirX;
	wallX -= floor(wallX);
	int what_tex = what_dir(gbl);
	int texX = (int)(wallX * (double)gbl->tex_tab[what_tex]->texWidth);
	if(gbl->rc->side == 0 && gbl->rc->rayDirX > 0)
		texX = gbl->tex_tab[what_tex]->texWidth - texX - 1;
    if(gbl->rc->side == 1 && gbl->rc->rayDirY < 0)
		texX = gbl->tex_tab[what_tex]->texWidth - texX - 1;    
	double step = 1.0 * gbl->tex_tab[what_tex]->texHeight / gbl->rc->lineheight;
	double texPos = (gbl->rc->drawstart /*- pitch*/ - HEIGHT / 2 + gbl->rc->lineheight / 2) * step;
	for(int y = gbl->rc->drawstart; y < gbl->rc->drawend; y++)
	{
		int texY = (int)texPos & (gbl->tex_tab[what_tex]->texHeight - 1);
		texPos += step;
		tmp = gbl->tex_tab[what_tex]->addr + (texY * gbl->tex_tab[what_tex]->line_length + texX * (gbl->tex_tab[what_tex]->bpp / 8));
		color = *(unsigned int*)tmp;
		if(gbl->rc->side == 1) 
			color = (color >> 1) & 8355711;
		put_pixel_image(gbl->mlx, x, y, color);
	}
}

void	trace_stripe(t_gbl *gbl, int x)
{
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
}