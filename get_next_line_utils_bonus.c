/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:52:55 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/08/08 15:57:02 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	if (i > 0)
		return (i);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	str_len;
	size_t	j;

	j = 0;
	str_len = 0;
	while (src[str_len] != '\0')
		str_len++;
	if (size == 0)
		return (str_len);
	while (src[j] != '\0' && j < size - 1)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (str_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_size;
	size_t	i;
	char	*n_string;

	s1_size = ft_strlen(s1);
	n_string = (char *)malloc(s1_size + ft_strlen(s2) + 1);
	if (!n_string)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		n_string[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		n_string[s1_size] = s2[i];
		i++;
		s1_size++;
	}
	n_string[s1_size] = '\0';
	return (n_string);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp_mem;
	size_t			i;

	temp_mem = malloc(count * size);
	i = 0;
	if (!temp_mem)
		return (NULL);
	while (i < count * size)
	{
		temp_mem[i] = 0;
		i++;
	}
	return (temp_mem);
}
