/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:20:12 by maroly            #+#    #+#             */
/*   Updated: 2022/03/29 20:35:05 by maroly           ###   ########.fr       */
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
	size_t	i;
	size_t	string;
	char	**tab;

	i = 0;
	string = 0;
	if (!s)
		return (NULL);
	tab = (char **) malloc(sizeof(*tab) * (create_tab(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (s[i])
	{
		if (((i == 0 || s[i - 1] == c) && s[i] != c) && s[i])
		{
			tab[string] = put_str_in_tab(&s[i], c);
			if (!tab[string])
			{
				destroy_tab(tab);
				err_exit(gbl);
			}
			string++;
		}
		i++;
	}
	tab[string] = NULL;
	return (tab);
}
