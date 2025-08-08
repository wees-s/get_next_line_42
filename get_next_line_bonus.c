/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:00:01 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/08/08 18:35:43 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	count_stash(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

static char	*ft_stralloc(const char *s1)
{
	char	*s2;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s2 = malloc(size * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}

static char	*free_all(char **buffer, char **stash)
{
	if ((buffer && *buffer) && (stash && *stash))
	{
		free(*buffer);
		*buffer = NULL;
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

static char	*finalize_line(char **stash, char **buffer)
{
	char	*res;
	char	*temp;

	if ((!*stash || (*stash)[0] == 0) && (*buffer)[0] == 0)
		return (free_all(buffer, stash));
	free(*buffer);
	*buffer = NULL;
	res = ft_calloc(count_stash(*stash) + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, *stash, count_stash(*stash) + 1);
	temp = ft_stralloc(*stash + count_stash(*stash));
	free(*stash);
	*stash = temp;
	return (res);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*temp;
	static char	*stash[1024];
	int			check;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(*buffer));
	check = 1;
	while (check > 0 && !ft_strchr(stash[fd], '\n'))
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check < 0)
			return (free_all(&buffer, &stash[fd]));
		buffer[check] = '\0';
		temp = stash[fd];
		stash[fd] = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (finalize_line(&stash[fd], &buffer));
}
