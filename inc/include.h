/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:36:24 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 12:46:30 by hkovac           ###   ########.fr       */
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
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ESC 53

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