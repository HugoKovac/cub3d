/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:52:03 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 02:29:02 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int is_pixel_around(t_gbl *gbl, int x, int y, t_square sq)
{
    int dist;
    
    dist = sqrt((gbl->rc->posX * sq.length + sq.marge - x) * (gbl->rc->posX
        * sq.length + sq.marge - x) + (gbl->rc->posY * sq.length + sq.marge - y)
        * (gbl->rc->posY * sq.length + sq.marge - y));
    if (dist <= 8 * sq.length)
        return (0);
    return (1);
}

void    print_square(t_square sq, t_gbl *gbl, int sign)
{
    int x;
    int y;

    y = -1;
    while (++y < sq.length)
    {
        x = -1;
        while (++x < sq.length)
        {
            if (sign == 0 && is_pixel_around(gbl, sq.x + x, sq.y + y, sq) == 0)
                put_pixel_image(gbl->mlx, sq.x + x, sq.y + y, sq.color);
            else if (sign == 1)
                put_pixel_image(gbl->mlx, sq.x + x, sq.y + y, sq.color);
        }
    }
}

int find_ratio(t_gbl *gbl)
{
    int x;
    int y;
    int tmp;
    double r_mp;
    double r_sq;

    tmp = 0;
    y = -1;
    while (gbl->map[++y])
    {
        x = -1;
        while (gbl->map[y][++x])
            if (x > tmp)
                tmp = x;
    }
    x = tmp;
    if (HEIGHT > WIDTH)
        r_mp = HEIGHT / 3.5;
    else
        r_mp = WIDTH / 3.5;
    if (x > y)
        r_sq = r_mp / x;
    else
        r_sq = r_mp / y;
    return (r_sq);
}

void    print_map(t_gbl *gbl) // todo : map mobile, player fixe
{
    double r_sq;
    int y;
    int x;
    t_square sq;

    y = -1;
    r_sq = find_ratio(gbl);
    while (gbl->map[++y])
    {
        x = -1;
        while (gbl->map[y][++x])
        {
            sq.marge = HEIGHT * 0.025;
            sq.x = x * r_sq + sq.marge;
            sq.y = y * r_sq + sq.marge;
            sq.length = r_sq;
            if (gbl->map[y][x] == '1')
            {
                sq.color = 0x000000;
                print_square(sq, gbl, 0);
            }
            else if (gbl->map[y][x] != ' ')
            {
                sq.color = 0xFFFFFF;
                print_square(sq, gbl, 0);
            }
        }
    }
    sq.x = gbl->rc->posX * r_sq + sq.marge;// - (gbl->rc->posX * 0.05);
    sq.y = gbl->rc->posY * r_sq + sq.marge;// - (gbl->rc->posY * 0.05); // marqueur pas bien centre
    sq.length = r_sq / 2;
    sq.color = 0xFF0000;
    print_square(sq, gbl, 1);
}