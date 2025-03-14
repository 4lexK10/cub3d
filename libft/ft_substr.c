/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:39:40 by akloster          #+#    #+#             */
/*   Updated: 2025/03/14 19:39:19 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*special_cases(void);
static size_t	ft_strlen_mod(const char *s);
static size_t	sub_strlen(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub_s;

	if (!s)
		return (NULL);
	i = (size_t) start;
	j = 0;
	if (len == 0 || start > ft_strlen_mod(s) - 1)
		return (special_cases());
	sub_s = (char *)malloc((sub_strlen(s, start, len) + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	while (s[i] != '\0' && j < len)
	{
		sub_s[i - start] = s[i];
		++i;
		++j;
	}
	sub_s[i - start] = '\0';
	return (sub_s);
}

static char	*special_cases(void)
{
	char	*sub_s;

	sub_s = (char *)malloc(1 * sizeof(char));
	if (!sub_s)
		return (NULL);
	sub_s[0] = '\0';
	return (sub_s);
}

static size_t	ft_strlen_mod(const char *s)
{
	size_t	i;
	char	*str;

	if (s[0] == '\0')
		return (1);
	str = (char *) s;
	if (!s)
		++str[0];
	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

static size_t	sub_strlen(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		++i;
		++j;
	}
	return (i - start);
}

/* #include <stdio.h>

int main(void)
{
	char str[] = "hello";
	unsigned int start = 6;
	size_t max = 10;
	char *sub_str = ft_substr(str, start, max);
	printf("%s$\n", sub_str);
	if (!sub_str)
		return (0);
	free(sub_str);
	return (0);
} */