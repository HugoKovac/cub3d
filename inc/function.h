/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:48:21 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/24 11:35:13 by hkovac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# define WALL_WIDTH  860
# define WALL_HEIGHT 640

/*get_next_line*/
char	*strmcat(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*freenquit(char *free1, char *free2, char *rtn);
int		ft_strlen(char *str);
int		ft_check(char *str);
char	*get_next_line(int fd);
/*utils_free.c*/
void	destroy_tab(char **tab);
void    close_tex(t_tex *tex);
int		end_free(t_gbl *gbl);
/*parse_map.c*/
int		parse_map(t_gbl *gbl, char *file);
/*exit.c*/
int		err_exit(t_gbl *gbl);
/*utils_str.c*/
int		ft_strncmp(const char *s1, const char *s2, int n);
/*check_cub.c*/
void	all_param(t_gbl *gbl);
int		check_char(char c);
int		count_island(t_gbl *gbl);
/*check_cub2.c*/
void	check_map_form(t_gbl *gbl);
void	check_map_char(t_gbl *gbl);
int		is_j_in(char *str, int j);
/*ray_casting.c*/
int     ray_casting(t_gbl *gbl);
/*draw.c*/
void    init_mlx(t_mlx *mlx, int x, int y);
void	draw_line(t_pos beg, t_pos end, t_mlx *mlx, unsigned int color);
/*open_texture.c*/
void    open_texture(t_gbl *gbl);


#endif
