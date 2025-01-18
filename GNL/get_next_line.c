/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:14:23 by lboumahd          #+#    #+#             */
/*   Updated: 2025/01/15 16:06:15 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_update(char *remains)
{
	char *new_remains;
	int i;
	int j;

	i = 0;
	j = 0;
	while (remains[i] && remains[i] != '\n')
		i++;
	if(!remains[i])
	{
		free(remains);
		return(NULL);
	}
	new_remains = malloc(ft_strlen(remains) - i + 1);
	if(!new_remains)
	{
		free(remains);
		return(NULL);
	}
	i++;
	while(remains[i])
		new_remains[j++] = remains[i++];
	new_remains[j] = '\0';
	free(remains);
	return(new_remains);
}
char *get_new_line(char *remains)
{
	char *new_line;
	int i;

	i = 0;
	if(!remains[i])
		return(NULL);
	while(remains[i] && remains[i] != '\n')
		i++;
	if(remains[i] == '\n')
		new_line = ft_substr(remains, 0, i + 1);
	else
		new_line = ft_substr(remains, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char *ft_read_file(char *remains, int fd)
{
	char *buffer;
	int read_bytes;

	read_bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if(!buffer)
	{
		free(remains);
		return (NULL);
	}
	while(read_bytes != 0 && !ft_strchr(remains, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if(read_bytes < 0)
		{
			free(buffer);
			free(remains);
			return(NULL);
		}
		buffer[read_bytes] = '\0';
		remains = ft_strjoin(remains, buffer);
	}
	free(buffer);
	return (remains);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*remains;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd >= 256)
		return NULL;
	remains = ft_read_file(remains, fd);
	if(!remains)
		return(NULL);
	new_line = get_new_line(remains);
	if(!new_line)
	{
		if(remains)
		{
			free(remains);
			remains = NULL;
		}
		return(NULL);
	}
	remains = ft_update(remains);
	return(new_line);
}


// // int    main(void)
// {
//     char    *line;
//     int        i;
//     int        fd;
//     fd = open("file1.txt", O_RDONLY);
//     i = 1;
//     // while (i < 7)
//     // {
//     //     line = get_next_line(fd);
//     //     printf("line [%02d]: %s", i, line);
//     //     free(line);
//     //     i++;
//     // }
// 	if (i == -1)
// 	{
// 		printf("<ERROR>\n");
// 		close(fd);
// 		return (-1);
// 	}
//     close(fd);
//     return (0);
// }
