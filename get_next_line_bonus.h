/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:53:26 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/08/08 18:42:51 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "unistd.h"
# include "fcntl.h"
# include "sys/types.h"
# include "stdlib.h"

char				*get_next_line(int fd);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *string);
char				*ft_strdup(const char *s1);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_calloc(size_t count, size_t size);
static char			*finalize_line(char **stash, char **buffer);
static char			*free_all(char **buffer, char **stash);
static size_t		count_stash(char *stash);

#endif
