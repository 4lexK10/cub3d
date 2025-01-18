/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linaboumahdi <linaboumahdi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:21:25 by lboumahd          #+#    #+#             */
/*   Updated: 2025/01/07 09:28:32 by linaboumahd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if(!s)
		return (0);

	i = 0;
	while (s[i])
		i++;
	return (i);
 }

char *ft_strjoin(char *s1, char *s2)
{
	char *res;
	int i;

	i = -1;
	if(!s1)
	{
		s1 = malloc(1);
		if(!s1)
			return(NULL);
		s1[0] = '\0';
	}
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if(!res)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	while(s1[++i])
		res[i] = s1[i];
	free(s1);
	while(*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return(res);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;
	size_t	len_p;

	i = 0;
	if (!s)
		return (NULL);
	len_p = ft_strlen(s);
	if(((len_p - start) > len) && (start < len_p))
		a = malloc(len + 1);
	else if (start > len_p)
		a = malloc(sizeof(char));
	else
		a = malloc((len_p - start) +1);
	if (!a)
	{	
		return (NULL);
	}
	if(start < len_p)
	{
		while (i < len && s[start])
			a[i++] = s[start++];
	}
	a[i] = '\0';
	return (a);
}


char	*ft_strchr(const char *s, int c)
{
	if(!s)
		return(NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	else
		return (NULL);
}
