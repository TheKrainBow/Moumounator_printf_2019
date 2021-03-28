/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:54:18 by magostin          #+#    #+#             */
/*   Updated: 2021/03/28 18:22:05 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"
# define BRED   "\x1B[1;31m"
# define BGRN   "\x1B[1;32m"
# define BYEL   "\x1B[1;33m"
# define BBLU   "\x1B[1;34m"
# define BMAG   "\x1B[1;35m"
# define BCYN   "\x1B[1;36m"
# define BWHT   "\x1B[1;37m"

typedef struct		s_nxtlne
{
	int				fd;
	char			*line;
}					t_nxtlne;

char				*ft_strjoin(char const *s1, char const *s2);
int					get_next_line(int fd, char **line);
char				*ft_gnl_strchr(char *s, int c);
char				*ft_gnl_strdup(const char *str);
char				*ft_gnl_strndup(const char *s, int n);
char				*ft_strnew(size_t size);
int					ft_gnl_strlen(const char *str);

#endif
