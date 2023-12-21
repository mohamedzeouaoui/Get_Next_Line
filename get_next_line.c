/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:40:29 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/12/16 11:40:32 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	count_c(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		i++;
	}
    i++;
	return (i);
}

int cheker(char *readbuf)
{
    int i;

    i = 0;
    while (readbuf[i] != '\0')
    {
        if (readbuf[i] == '\n')
            return(1);
        i++;
    }
    return(0);
}

char    *rest(char *readbuf)
{
    int i;
    int j;
    char *str = malloc(BUFFER_SIZE + 1); /*********************/
    j = 0;
    i = 0;
    while (readbuf[i] != '\0')
    {
        if (readbuf[i] == '\n')
        {
            i++;
            while (readbuf[i] != '\0')
            {
                str[j] = readbuf[i];
                i++;
                j++;
            }
            continue;
        }
        i++;
    }
    str[j] = '\0';
    return(str);
}

char *ft_return(char *line)
{
    if (ft_strlen(line) > 0)
        return (line);
    else
        return (free(line), NULL);
}

char *get_next_line(int fd)
{
    if (fd < 0)
        return(NULL);
    char readbuf[BUFFER_SIZE + 1];
    char *line;
    static char *resetstr;
    int readed;
    int i;
    char    c;
    // static int k;
    i = 0;
    //printf("__________________%d__________________\n", k++);
    line = malloc(1); /************************/
    line[0] = '\0';
    c = 0;
    if (resetstr != NULL)
    {
        line = ft_strjoin(line, resetstr);
        // printf("line with rest: \"%s\"\n", line);
        free(resetstr);
        resetstr = NULL;
    }
    while (c != 2)
    {
        i = 0;
        readed = read(fd, readbuf, BUFFER_SIZE);
        // printf("readed: \"%d\"\n", readed);
        if (readed == 0)
            return (ft_return(line));
        readbuf[readed] = '\0';
        // printf("readbuf: \"%s\"\n", readbuf);
        line = ft_strjoin(line, readbuf);
        // printf("line in gnl: \"%s\"\n", line);
        c = cheker(readbuf);
        if (c == 1)
        {
            resetstr = rest(readbuf);
            // printf("resetstr: \"%s\"\n", resetstr);
        }
        c++;
    }
    i = 0;
    i = count_c(line);
    return(ft_substr(line, 0, i));
}

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
//             break;
//     }
//     str = get_next_line(a);
//     printf("line: \"%s\"\n", str);
//     free(str);
//     return 0;
// }
