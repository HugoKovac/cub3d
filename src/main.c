/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:22:18 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/17 16:01:58 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int main(int ac, char **av)
{
	t_gbl *gbl;

	if (ac != 2)
		return (1);
	gbl = malloc(sizeof(t_gbl));
	*gbl = (t_gbl){0};
	parse_map(gbl, av[1]);
	return (end_free(gbl));
}