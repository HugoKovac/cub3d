/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:42:38 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/15 18:50:29 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*del_b(char *str)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (freenquit(str, NULL, NULL));
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	else
		i++;
	rtn = malloc (sizeof (char) * (ft_strlen(&str[i]) + 1));
	if (!rtn)
		return (NULL);
	j = 0;
	while (str[i])
	{
		rtn[j] = str[i];
		i++;
		j++;
	}
	rtn[j] = 0;
	return (rtn);
}

char	*del_a(char *str)
{
	char	*rtn;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (freenquit(str, NULL, ft_strdup(str)));
	rtn = malloc(sizeof (char) * (i + 1));
	if (!rtn)
		return (freenquit(str, NULL, NULL));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = 0;
	return (freenquit(str, NULL, rtn));
}

char	*ft_read(char *before, int fd)
{
	char	*buffer;
	int		r_rtn;
	char	*rtn;

	r_rtn = 1;
	rtn = NULL;
	if (before)
	{
		rtn = ft_strdup(before);
		free(before);
	}
	while (!ft_check(rtn) && r_rtn != 0)
	{
		buffer = malloc(sizeof (char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		r_rtn = read(fd, buffer, BUFFER_SIZE);
		if (r_rtn <= 0)
			return (freenquit(buffer, NULL, rtn));
		buffer[r_rtn] = 0;
		rtn = strmcat (rtn, buffer);
	}
	if (!rtn)
		return (NULL);
	return (rtn);
}

char	*get_next_line(int fd)
{
	char		*rtn;
	static char	*save = NULL;

	rtn = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rtn = ft_read(save, fd);
	if (!rtn)
		return (freenquit(rtn, save, NULL));
	if (!*rtn)
	{
		free(rtn);
		rtn = NULL;
	}
	save = del_b(rtn);
	rtn = del_a(rtn);
	if (!rtn)
		free(save);
	return (rtn);
}
