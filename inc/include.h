/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:36:24 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 14:36:05 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# define BUFFER_SIZE 10

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 4
# define C 5


# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC 65307

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include "struct.h"
# include "function.h"

#endif