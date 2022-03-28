/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:02:13 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/28 18:18:59 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void    open_texture(t_gbl *gbl)
{
    t_mlx   **tex;
    int     i;

    i = -1;
    tex = malloc(sizeof(t_mlx *) * 4);
    while (++i < 4)
    {
        tex[i] = malloc(sizeof(t_mlx));
        *tex[i] = (t_mlx){0};
	    tex[i]->img = mlx_xpm_file_to_image(gbl->mlx->mlx, gbl->tex_string[i], &tex[i]->texWidth, &tex[i]->texHeight);
        printf("%s\n", gbl->tex_string[i]);
        printf("%p\n", tex[i]->img);
        if (!tex[i]->img)
        {
            write(1, "Error\nProblem when opening texture\n", ft_strlen("Error\nProblem when opening texture\n"));
            err_exit(gbl);
        }
	    tex[i]->addr = mlx_get_data_addr(tex[i]->img, &tex[i]->bpp, &tex[i]->line_length, &tex[i]->endian);
    }
    gbl->tex_tab = tex;//to free
}