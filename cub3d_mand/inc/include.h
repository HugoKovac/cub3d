/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:36:24 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/02 20:54:32 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# define BUFFER_SIZE 10

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define DO 4
# define F 5
# define C 6

# define DOOR

# define WIDTH 860
# define HEIGHT 640

# define PI 3.1415926

//MacOS
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ESC 53
# define SHIFT 257
# define ARROW_UP 126
# define ARROW_DOWN 125

//LINUX
/*# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ESC 65307
# define SHIFT 65505
# define ARROW_UP 65362
# define ARROW_DOWN 65364*/
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
# include <pthread.h>

#endif