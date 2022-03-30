/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:58:58 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/30 02:45:56 by maroly           ###   ########.fr       */
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

int ft_atoi(const char *nptr, t_gbl *gbl)
{
        size_t	i;
        int	sign;
        int     result;

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
	if (result * sign < 0)
		err_exit(gbl);
        return (result * sign);
}
