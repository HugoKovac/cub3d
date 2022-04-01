/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:58:58 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/31 19:03:20 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (((unsigned char)s1[i] || (unsigned char)s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	check_ext(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (i >= 4)
		if (ft_strncmp(file + (i - 4), ".cub", 4) == 0)
			return (1);
	return (0);
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

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
			i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
				sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
			result = result * 10 + nptr[i] - 48;
			i++;
	}
	return (result * sign);
}
