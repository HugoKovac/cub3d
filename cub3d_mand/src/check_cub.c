/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:58:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/04 14:01:21 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	all_param2(t_gbl *gbl, int i)
{
	if (gbl->file[i][0] == '\0')
		return ;
	else if (ft_strncmp("NO ", gbl->file[i], 3) == 0)
		gbl->tex_string[NO] = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("SO ", gbl->file[i], 3) == 0)
		gbl->tex_string[SO] = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("WE ", gbl->file[i], 3) == 0)
		gbl->tex_string[WE] = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("EA ", gbl->file[i], 3) == 0)
		gbl->tex_string[EA] = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("F ", gbl->file[i], 2) == 0)
		gbl->tex_string[F] = ft_strdup(gbl->file[i] + 2);
	else if (ft_strncmp("C ", gbl->file[i], 2) == 0)
		gbl->tex_string[C] = ft_strdup(gbl->file[i] + 2);
	else
	{
		write (1, "Error\nIncorrect texture id\n",
			ft_strlen("Error\nIncorrect texture id\n"));
		err_exit(gbl);
	}
}

void	free_color(t_color *color)
{
	free(color->r);
	free(color->g);
	free(color->b);
	free(color->rg_hexa);
}

unsigned int	rgb_hexa2(t_color color)
{
	color.rg_hexa = ft_strcat(color.r, color.g);
	color.rgb_hexa = ft_strcat(color.rg_hexa, color.b);
	free_color(&color);
	color.rgb_dec = ft_convert_base(color.rgb_hexa,
			"0123456789abcdef", "0123456789");
	free(color.rgb_hexa);
	color.color = ft_atoi(color.rgb_dec);
	free(color.rgb_dec);
	return (color.color);
}

unsigned int	rgb_hexa(char *str, t_gbl *gbl)
{
	t_color	color;

	color.rgb = ft_split(str, ',', gbl);
	if (check_rgb(color.rgb) == 1)
	{
		write(2, "Error\nRGB code incorrect\n",
			ft_strlen("Error\nRGB code incorrect\n"));
		err_exit(gbl);
	}
	if (ft_atoi(color.rgb[0]) > 255 || ft_atoi(color.rgb[0]) < 0
		|| ft_atoi(color.rgb[1]) > 255
		|| ft_atoi(color.rgb[1]) < 0 || ft_atoi(color.rgb[2]) > 255
		|| ft_atoi(color.rgb[2]) < 0)
	{
		write (2, "Error\nProbleme with rgb code for F or C\n",
			ft_strlen("Error\nProbleme with rgb code for F or C\n"));
		err_exit(gbl);
	}
	color.r = ft_convert_base(color.rgb[0], "0123456789", "0123456789abcdef");
	color.g = ft_convert_base(color.rgb[1], "0123456789", "0123456789abcdef");
	color.b = ft_convert_base(color.rgb[2], "0123456789", "0123456789abcdef");
	destroy_tab(color.rgb);
	return (rgb_hexa2(color));
}

void	all_param(t_gbl *gbl)
{
	int		i;

	i = -1;
	while (++i < 6)
		gbl->tex_string[i] = NULL;
	i = -1;
	while (gbl->file[++i] && &gbl->file[i] != gbl->map)
		all_param2(gbl, i);
	if (!gbl->tex_string[NO] || !gbl->tex_string[SO] || !gbl->tex_string[WE]
		|| !gbl->tex_string[EA] || !gbl->tex_string[F]
		|| !gbl->tex_string[C])
	{
		write (1, "Error\nNot enough texture id\n",
			ft_strlen("Error\nNot enough texture id\n"));
		err_exit(gbl);
	}
	gbl->sky = rgb_hexa(gbl->tex_string[C], gbl);
	gbl->floor = rgb_hexa(gbl->tex_string[F], gbl);
}
