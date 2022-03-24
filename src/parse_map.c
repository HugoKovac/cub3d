/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:35:11 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 10:17:36 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

void	count_malloc_tab2d(t_gbl *gbl, int fd)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		count++;
		tmp = get_next_line(fd);
	}
	close (fd);
	gbl->file = malloc(sizeof(char *) * (count + 1));
	gbl->file[count] = NULL;
}

void	fill_tab2d(t_gbl *gbl, int fd)
{
	int	i;

	i = 0;
	while (1)
	{
		gbl->file[i] = get_next_line(fd);
		if (gbl->file[i] == NULL)
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
		perror("Error\nOpen map");
		err_exit(gbl);
	}
}

int    test_line(char *str)
{
    int i;
    int    count;
    
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '1')
            count++;
        if (str[i] != '1' && str[i] != ' ')
            return (0);
        i++;
    }
    if (count < 1)
        return (0);
    return (1);
}

void find_map(t_gbl *gbl)
{
    int    i;

    i = 0;
    while (gbl->file[i])
    {
        if (test_line(gbl->file[i]))
            break ;
        i++;
    }
    gbl->map = gbl->file + i;
}

int	parse_map(t_gbl *gbl, char *file)
{
	int	fd[2];

	if (!check_ext(file))
		return (0);
	open_fd(gbl, fd, file);
	count_malloc_tab2d(gbl, fd[0]);
	fill_tab2d(gbl, fd[1]);
	find_map(gbl);
	if (*gbl->map == NULL)
	{
		perror("Error\nFind map");
		err_exit(gbl);
	}
	all_param(gbl);
	check_map_form(gbl);
	check_map_char(gbl);
	return (1);
}
