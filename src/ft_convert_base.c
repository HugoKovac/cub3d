/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:50:19 by maroly            #+#    #+#             */
/*   Updated: 2022/03/30 03:02:42 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <include.h>

int	ft_atoi_base(char *nbr, char *base)
{
	int	result;
	int	count;
	int	i;

	i = 0;
	count = 1;
	result = 0;
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13)
		|| nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			count = -count;
		i++;
	}
	while (is_in_base(nbr[i], base))
	{
		result = result * ft_strlen(base) + find_index(nbr[i], base);
		i++;
	}
	return (result * count);
}

void	dec_to_base_to(long int nb, int size_of_base, char *str, char *base_to)
{
	int	i;
	int sign;

	i = len(nb, size_of_base);
	sign = 0;
	if (nb >=0 && nb <= 9)
	{
		sign = 1;
		i++;
	}
	str[i + 1] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (nb >= size_of_base)
	{
		str[i] = base_to[nb % size_of_base];
		nb = nb / size_of_base;
		i--;
	}
	str[i] = base_to[nb % size_of_base];
	if (sign == 1)
		str[--i] = '0';
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		intdecimal;
	char	*str;
	int		size_to_malloc;
	int		size_of_base_to;

	intdecimal = 0;
	size_of_base_to = ft_strlen(base_to);
	size_to_malloc = 0;
	intdecimal = ft_atoi_base(nbr, base_from);
	if (intdecimal >= 0 && intdecimal <= 9)
		size_to_malloc = len(intdecimal, size_of_base_to) + 3;
	else
		size_to_malloc = len(intdecimal, size_of_base_to) + 2;
	str = NULL;
	str = malloc(sizeof(char) * size_to_malloc);
	if (str == NULL)
		return (NULL);
	dec_to_base_to(intdecimal, size_of_base_to, str, base_to);
	return (str);
}
