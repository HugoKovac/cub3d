/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkovac <hkovac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:48:21 by hkovac            #+#    #+#             */
/*   Updated: 2022/03/16 16:10:14 by hkovac           ###   ########.fr       */
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


#endif
