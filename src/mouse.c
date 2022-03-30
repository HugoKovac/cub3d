/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:53:56 by maroly            #+#    #+#             */
/*   Updated: 2022/03/30 16:38:55 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int mouse(int x, int y, t_gbl *gbl)
{
    (void)y;
    gbl->count++;
    if (gbl->is_mouse_hide == true && gbl->count == 5)
    {
        if (x > WIDTH / 2)
            arrow_right(gbl);
        else if (x < WIDTH / 2)
            arrow_left(gbl);
        reframe(gbl);
        gbl->count = 0;
    }
    if (gbl->is_mouse_hide == true)
        mlx_mouse_move(gbl->mlx->mlx, gbl->mlx->mlx_win, WIDTH / 2, HEIGHT / 2);
    return (1);
}

int mouse_pressed(int button, int x, int y, t_gbl *gbl)
{
    (void)x;
    (void)y;
    if (gbl->is_mouse_hide == false && button == 1)
    {
        gbl->is_mouse_hide = true;
        gbl->count = 0;
        mlx_mouse_hide(gbl->mlx->mlx, gbl->mlx->mlx_win);
        mlx_mouse_move(gbl->mlx->mlx, gbl->mlx->mlx_win, WIDTH / 2, HEIGHT / 2);
    }
    else if (gbl->is_mouse_hide == true && button == 3)  
    {
        gbl->is_mouse_hide = false;
        mlx_mouse_move(gbl->mlx->mlx, gbl->mlx->mlx_win, WIDTH / 2, HEIGHT / 2);
        mlx_mouse_show(gbl->mlx->mlx, gbl->mlx->mlx_win);
    }
    return (1);
}