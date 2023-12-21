/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:40:58 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/12/16 11:41:07 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;


	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)); /*************/
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	return (free(s1), s3);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;
	int		i;

	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1)); /****************/
	if (ptr == NULL)
	{
		return (0);
	}
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char    *ft_substr(char *s, unsigned int start, size_t len)
{
	char	*nstr;
	size_t	lng;
	size_t	i;

	if (s == NULL)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s = s + start;
	lng = 0;
	while (s[lng] != '\0' && len > lng)
		lng++;
	nstr = malloc(sizeof(char) * (lng + 1)); /********************/
	if (nstr == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0' && len > i)
	{
		nstr[i] = s[i];
		i++;
	}
	nstr[i] = '\0';
	return (free(s), nstr);
}

