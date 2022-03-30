/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:58:23 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/30 03:03:23 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	all_param2(t_gbl *gbl, int i) // trop de possibilite de leaks
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
		write (1, "Error\nIncorrect texture id\n", ft_strlen("Error\nIncorrect texture id\n"));
		err_exit(gbl);
	}
}

char *str_triple_cat(char *s1, char *s2, char *s3)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	while (s1[i])
	{
		new[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		new[j] = s2[i];
		i++;
		j++;
	}
	i = 0;
	while (s3[i])
	{
		new[j] = s3[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

unsigned int rgb_hexa(char *str, t_gbl *gbl)
{
	char **rgb;
	char *R;
	char *G;
	char *B;
	char *rgb_hexa;
	char *rgb_dec;
	unsigned int color;

	rgb = ft_split(str, ',', gbl);
	R = ft_convert_base(rgb[0], "0123456789", "0123456789abcdef");
	G = ft_convert_base(rgb[1], "0123456789", "0123456789abcdef");
	B = ft_convert_base(rgb[2], "0123456789", "0123456789abcdef");
	destroy_tab(rgb);
	rgb_hexa = str_triple_cat(R, G, B);
	free(R);
	free(G);
	free(B);
	rgb_dec = ft_convert_base(rgb_hexa, "0123456789abcdef", "0123456789");
	color = ft_atoi(rgb_dec,  gbl);
	free(rgb_dec);
	return (color);
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
		|| !gbl->tex_string[EA] || !gbl->tex_string[F] || !gbl->tex_string[C])
	{
		write (1, "Error\nNot enough texture id\n", ft_strlen("Error\nNot enough texture id\n"));
		err_exit(gbl);
	}
	gbl->sky = rgb_hexa(gbl->tex_string[C], gbl);
	gbl->floor = rgb_hexa(gbl->tex_string[F], gbl);
}

int	check_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

void	check_map_char(t_gbl *gbl)
{
	int player;
	int i;
	int j;

	i = -1;
	player = 0;
	while (gbl->map[++i])
	{
		j = -1;
		while (gbl->map[i][++j])
			if (gbl->map[i][j] == 'N' || gbl->map[i][j] == 'E'
				|| gbl->map[i][j] == 'S' || gbl->map[i][j] == 'W')
				player++;
	}
	if (player != 1)
	{
		write(2, "Error\nWrong number of player\n", ft_strlen("Error\nWrong number of player\n"));
		err_exit(gbl);
	}
}
