/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:45:26 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 20:31:59 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	ft_check(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*freenquit(char *free1, char *free2, char *rtn)
{
	if (free1)
		free(free1);
	if (free2)
		free(free2);
	if (rtn)
		return (rtn);
	return (NULL);
}

char	*ft_strdup(char *str)
{
	char	*rtn;
	int		i;

	if (!str)
		return (NULL);
	rtn = malloc(sizeof (char) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = 0;
	return (rtn);
}

char	*strmcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*rtn;

	if (!s1 && !s2)
		return (freenquit(s1, s2, NULL));
	else if (!s1)
		return (freenquit(s2, NULL, ft_strdup(s2)));
	else if (!s2)
		return (freenquit(s1, NULL, ft_strdup(s1)));
	rtn = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		rtn[i] = s1[i];
		i++;
	}
	while (s2[j])
		rtn[i++] = s2[j++];
	rtn[i] = 0;
	return (freenquit(s1, s2, rtn));
}
