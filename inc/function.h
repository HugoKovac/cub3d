/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroly <maroly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:48:21 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/20 23:53:38 by maroly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

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
/*check_cub.c*/
void	all_param(t_gbl *gbl);
void	check_map_form(t_gbl *gbl);
void	check_map_char(t_gbl *gbl);
int		check_char(char c);
int		count_island(t_gbl *gbl);
int		is_j_in(char *str, int j);

#endif
