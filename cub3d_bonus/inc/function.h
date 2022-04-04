/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:48:21 by hkovac            #+#    #+#             */
/*   Updated: 2022/04/04 12:26:31 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

/*get_next_line*/
char			*strmcat(char *s1, char *s2);
char			*ft_strdup(char *str);
char			*freenquit(char *free1, char *free2, char *rtn);
int				ft_strlen(char *str);
int				ft_check(char *str);
char			*get_next_line(int fd);
/*utils_free.c*/
void			destroy_tab(char **tab);
int				end_free(t_gbl *gbl);
void			destroy_tex_mlx(t_mlx **tex_tab);
void			destroy_mlx(t_mlx *mlx);
void			destroy_tex(char *tab[6]);
/*parse_map.c*/
int				parse_map(t_gbl *gbl, char *file);
/*exit.c*/
int				err_exit(t_gbl *gbl);
/*utils_str.c*/
int				ft_strncmp(const char *s1, const char *s2, int n);
int				ft_atoi(const char *nptr);
int				check_ext(char *file);
void			fill_tab2d(t_gbl *gbl, int fd);
/*check_cub.c*/
void			all_param(t_gbl *gbl);
int				check_char(char c);
/*count_island.c*/
int				count_island(t_gbl *gbl);
/*count_island_utils.c*/
bool			**init_map(t_gbl *gbl);
int				ft_biglen(char **tab);
void			*ft_memset(void *s, int c, size_t n);
void			free_tab(bool **tab, int row);
/*check_cub2.c*/
int				is_j_in(char *str, int j);
int				max_len(t_gbl *gbl);
int				door_places(t_gbl *gbl);
/*check_cub3.c*/
int				check_char(char c);
void			check_map_form(t_gbl *gbl);
void			check_map_char(t_gbl *gbl);
/*check_handv.c*/
int				check_map_horizontal(t_gbl *gbl);
int				check_map_vertical(t_gbl *gbl);
/*ray_casting.c*/
void			start(t_rc *rc, t_gbl *gbl);
int				ray_casting(t_gbl *gbl);
unsigned int	rgb_file(char *str, t_gbl *gbl);
/*ray_casting_utils.c*/
void			find_side(t_rc *rc);
void			init_calcul(t_rc *rc, int x);
/*draw.c*/
void			init_mlx(t_mlx *mlx, int x, int y);
void			draw_line(t_pos beg, t_pos end, t_mlx *mlx, unsigned int color);
void			put_pixel_image(t_mlx *mlx, int x, int y, unsigned int color);
/*open_texture.c*/
void			open_texture(t_gbl *gbl);
/*texturing.c*/
int				what_dir(t_gbl *gbl);
void			stripe_tex(t_gbl *gbl, int x);
void			trace_stripe(t_gbl *gbl, int x);
/*init_player.c*/
int				find_pos(t_gbl *gbl, t_rc *rc);
void			init_dir(t_gbl *gbl, t_rc *rc);
/*utils_mlx.c*/
void			re_win(t_gbl *gbl);
int				destroy_window(t_gbl *gbl);
/*controls.c*/
int				controls(int keycode, t_gbl *gbl);
void			head_up(t_gbl *gbl, int mult);
void			head_down(t_gbl *gbl, int mult);
void			arrow_left(t_gbl *gbl, int mult);
void			arrow_right(t_gbl *gbl, int mult);
/*controls_wasd.c*/
void			up(t_gbl *gbl);
void			down(t_gbl *gbl);
void			right(t_gbl *gbl);
void			left(t_gbl *gbl);
void			shift(t_gbl *gbl);
/*split.c*/
char			**ft_split(char const *s, char c, t_gbl *gbl);
/*ft_convert_base.c*/
int				len(int nb, int size_of_base);
int				is_in_base(char c, char *base);
int				find_index(char c, char *base);
char			*ft_convert_base(char *nbr, char *base_from, char *base_to);
/*mouse.c*/
int				mouse(int x, int y, t_gbl *gbl);
int				mouse_pressed(int button, int x, int y, t_gbl *gbl);
/*mini_map.c*/
void			print_map(t_gbl *gbl);
/*background.c*/
void			floor_sky(t_gbl *gbl);

#endif
