/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:58:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/02 14:10:21 by maroly           ###   ########.fr       */
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
	else if (ft_strncmp("DO ", gbl->file[i], 3) == 0)
		gbl->tex_string[DO] = ft_strdup(gbl->file[i] + 3);
	else if (ft_strncmp("CL ", gbl->file[i], 3) == 0)
		gbl->tex_string[CL] = ft_strdup(gbl->file[i] + 3);
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

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i])
	{
		new[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new[j] = s2[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

void	free_color(t_color *color)
{
	free(color->r);
	free(color->g);
	free(color->b);
	free(color->rg_hexa);
}

unsigned int	rgb_hexa(char *str, t_gbl *gbl)
{
	t_color	color;

	color.rgb = ft_split(str, ',', gbl);
	color.r = ft_convert_base(color.rgb[0], "0123456789", "0123456789abcdef");
	color.g = ft_convert_base(color.rgb[1], "0123456789", "0123456789abcdef");
	color.b = ft_convert_base(color.rgb[2], "0123456789", "0123456789abcdef");
	destroy_tab(color.rgb);
	if (ft_atoi(color.r) > 255 || ft_atoi(color.r) < 0
		|| ft_atoi(color.g) > 255
		|| ft_atoi(color.g) < 0 || ft_atoi(color.b) > 255
		|| ft_atoi(color.b) < 0)
	{
		write (2, "Error\nProbleme with rgb code for F or C\n",
			ft_strlen("Error\nProbleme with rgb code for F or C\n"));
		err_exit(gbl);
	}
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

void	all_param(t_gbl *gbl)
{
	int		i;

	i = -1;
	while (++i < 7)
		gbl->tex_string[i] = NULL;
	i = -1;
	while (gbl->file[++i] && &gbl->file[i] != gbl->map)
		all_param2(gbl, i);
	if (!gbl->tex_string[NO] || !gbl->tex_string[SO] || !gbl->tex_string[WE]
		|| !gbl->tex_string[EA] || !gbl->tex_string[F]
		|| !gbl->tex_string[C] || !gbl->tex_string[DO])
	{
		write (1, "Error\nNot enough texture id\n",
			ft_strlen("Error\nNot enough texture id\n"));
		err_exit(gbl);
	}
	gbl->sky = rgb_hexa(gbl->tex_string[C], gbl);
	gbl->floor = rgb_hexa(gbl->tex_string[F], gbl);
}
