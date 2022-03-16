/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:35:11 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/16 17:05:54 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void count_malloc_tab2d(t_gbl *gbl, int fd)
{
	int	count;
	char *tmp;
	
	count = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		count++;
		tmp = get_next_line(fd);
	}
	close (fd);
	gbl->map = malloc(sizeof(char *) * (count + 1));
	gbl->map[count] = NULL;
}

void fill_tab2d(t_gbl *gbl, int fd)
{
	int	i;
	
	i = 0;
	while (1)
	{
		gbl->map[i] = get_next_line(fd);
		if (gbl->map[i] == NULL)
			break ;
		i++;
	}
	close (fd);
}

int	check_ext(char *file)
{
	int	i;
	
	i = 0;
	while (file[i])
		i++;
	if (i >= 4)//doit accepter seulement ".cub"?
		if (ft_strncmp(file + (i - 4), ".cub", 4) == 0)
			return (1);
	return (0);
}

void	open_fd(t_gbl *gbl, int fd[2], char *file)
{
	fd[0] = open(file, O_RDONLY);
	fd[1] = open(file, O_RDONLY);
	if (fd[0] < 0 || fd[1] < 0)
	{
		perror("cub3d (parse_map.c)");	
		err_exit(gbl);
	}
}

int	parse_map(t_gbl *gbl, char *file)
{
	int fd[2];
	
	if (!check_ext(file))
		return (0);
	open_fd(gbl, fd, file);
	count_malloc_tab2d(gbl, fd[0]);
	fill_tab2d(gbl, fd[1]);
	// check_map_head();
	// check_map_form();
	return (1);
}