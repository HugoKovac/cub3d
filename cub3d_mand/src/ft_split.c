/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:20:12 by maroly            #+#    #+#             */
/*   Updated: 2022/03/31 19:30:42 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <include.h>

static int	create_tab(char const *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (((i == 0 || s[i - 1] == c) && s[i] != c) && s[i])
			size++;
		i++;
	}
	return (size);
}

static char	*put_str_in_tab(const char *s, char c)
{
	size_t	i;
	char	*str;

	str = NULL;
	i = 0;
	while (s[i] != c && s[i])
		i++;
	str = (char *) malloc(sizeof(*str) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c, t_gbl *gbl)
{
	t_split	a;

	a.i = 0;
	a.string = 0;
	if (!s)
		return (NULL);
	a.tab = (char **) malloc(sizeof(*a.tab) * (create_tab(s, c) + 1));
	if (a.tab == NULL)
		return (NULL);
	while (s[a.i])
	{
		if (((a.i == 0 || s[a.i - 1] == c) && s[a.i] != c) && s[a.i])
		{
			a.tab[a.string] = put_str_in_tab(&s[a.i], c);
			if (!a.tab[a.string])
			{
				destroy_tab(a.tab);
				err_exit(gbl);
			}
			a.string++;
		}
		a.i++;
	}
	a.tab[a.string] = NULL;
	return (a.tab);
}
