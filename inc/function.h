/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:48:21 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/29 18:33:01 by maroly           ###   ########.fr       */
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
int		end_free(t_gbl *gbl);
/*parse_map.c*/
int		parse_map(t_gbl *gbl, char *file);
/*exit.c*/
int		err_exit(t_gbl *gbl);
/*utils_str.c*/
int		ft_strncmp(const char *s1, const char *s2, int n);
char     ft_atoi(const char *nptr, t_gbl *gbl);
/*check_cub.c*/
void	all_param(t_gbl *gbl);
int		check_char(char c);
int		count_island(t_gbl *gbl);
/*check_cub2.c*/
void	check_map_form(t_gbl *gbl);
void	check_map_char(t_gbl *gbl);
int		is_j_in(char *str, int j);
/*ray_casting.c*/
void start(t_rc *rc, t_gbl *gbl);
int     ray_casting(t_gbl *gbl);
/*draw.c*/
void    init_mlx(t_mlx *mlx, int x, int y);
void	draw_line(t_pos beg, t_pos end, t_mlx *mlx, unsigned int color);
void    put_pixel_image(t_mlx *mlx, int x, int y, unsigned int color);
/*open_texture.c*/
void    open_texture(t_gbl *gbl);
/*controls.c*/
int	controls(int keycode, t_gbl *gbl);
/*texturing.c*/
int		what_dir(t_gbl *gbl);
void	stripe_tex(t_gbl *gbl, int x);
void	trace_stripe(t_gbl *gbl, int x);
/*init_player.c*/
int	find_pos(t_gbl *gbl, t_rc *rc);
void init_dir(t_gbl *gbl, t_rc *rc);
/*utils_mlx.c*/
void    re_win(t_gbl *gbl);
int	destroy_window(t_gbl *gbl);
void	reframe(t_gbl *gbl);
/*controls.c*/
int	controls(int keycode, t_gbl *gbl);
/*split*/
char	**ft_split(char *str, char *charset);

#endif
