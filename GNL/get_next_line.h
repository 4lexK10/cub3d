/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linaboumahdi <linaboumahdi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:22:56 by lboumahd          #+#    #+#             */
/*   Updated: 2025/01/07 00:57:36 by linaboumahd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif
# if BUFFER_SIZE > 10000
# undef BUFFER_SIZE
# define BUFFER_SIZE 1000
# endif 

char	*get_next_line(int fd);
char *ft_read_file(char *remains, int fd);
char *get_new_line(char *remains);
char *ft_update(char *remains);
size_t	ft_strlen(const char *s);
char *ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);

#endif


