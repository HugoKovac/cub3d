/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:02:13 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 15:11:55 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void    open_texture(t_gbl *gbl)
{
    t_tex *tex;

    tex = malloc(sizeof(t_tex));//to_free
    if (!tex)
    {
        perror("Error\nMalloc t_tex");
        err_exit(gbl);
    }
    *tex = (t_tex){0};
    tex->fd_NO = open(gbl->no, O_RDONLY);
    tex->fd_SO = open(gbl->so, O_RDONLY);
    tex->fd_WE = open(gbl->we, O_RDONLY);
    tex->fd_EA = open(gbl->ea, O_RDONLY);
    gbl->tex = tex;
    if (tex->fd_NO < 0 || tex->fd_SO < 0 || tex->fd_WE < 0 || tex->fd_EA < 0)
    {
        perror("Error\nOpen texture");
        err_exit(gbl);
    }
}