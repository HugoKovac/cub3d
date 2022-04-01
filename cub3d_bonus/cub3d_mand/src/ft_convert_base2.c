/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:51:00 by maroly            #+#    #+#             */
/*   Updated: 2022/03/30 02:29:40 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	len(int nb, int size_of_base)
{
	int			size;
	long int	nbr;

	size = 0;
	nbr = nb;
	if (nbr == -2147483648)
	{
		nbr = -nbr;
		size++;
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		size++;
	}
	if (nbr < size_of_base)
		return (size);
	while (nbr >= size_of_base)
	{
		nbr = nbr / size_of_base;
		size++;
	}
	return (size);
}

int	is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	find_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (0);
}
