/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:42:35 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/12/24 19:43:07 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*redlang_line(char *str, int fd, char *buffer)
{
	int	nmbre_byte;

	nmbre_byte = 1;
	while (nmbre_byte > 0 && !ft_strchr(str, '\n'))
	{
		nmbre_byte = read(fd, buffer, BUFFER_SIZE);
		if (nmbre_byte == -1)
			return (free(buffer), free(str), NULL);
		else if (nmbre_byte == 0)
		{
			if (ft_strlen(str) > 0)
				return (free(buffer), str);
			else
				return (free(buffer), free(str), NULL);
		}
		buffer[nmbre_byte] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (free(buffer), str);
}

char	*correcte_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*rest_line(char *str, char *line)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rest = malloc(ft_strlen(str) - ft_strlen(line) + 1);
	if (!rest)
		return (free(str), NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		i++;
		while (str[i])
		{
			rest[j] = str[i];
			i++;
			j++;
		}
	}
	rest[j] = '\0';
	return (free(str), rest);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str[fd] == NULL)
	{
		str[fd] = malloc(1);
		str[fd][0] = '\0';
		if (str[fd] == NULL)
			return (NULL);
	}
	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (free(str[fd]), NULL);
	str[fd] = redlang_line(str[fd], fd, buffer);
	if (!str[fd])
		return (NULL);
	line = correcte_line(str[fd]);
	str[fd] = rest_line(str[fd], line);
	if (!str[fd])
		return (free(line), NULL);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
//     char *str;
//     int a = open("file.txt", O_RDONLY);
//     while (1)
//     {
//         str = get_next_line(a);
//         printf("line: \"%s\"\n", str);
//         free(str);
//         if (!str)
//             break ;
//     }
//     str = get_next_line(a);
//     printf("line: \"%s\"\n", str);
//     free(str);
//     return (0);
// }
