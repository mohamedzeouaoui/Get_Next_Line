/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:05:53 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/12/21 15:05:57 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

char	*ft_strjoin(char *s1, char *s2);
char *get_next_line(int fd);
char    *ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);

#endif
