/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon.lau <simon.lau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 21:05:45 by simon.lau         #+#    #+#             */
/*   Updated: 2026/10/15 14:02:02 by simon.lau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_to_stash(char *stash, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buf);
	free(stash);
	return (tmp);
}

static char	*refill_stash_from_fd(char *buf, int fd, char *stash)
{
	ssize_t	bytes;

	while (ft_strchr(stash, SEP_CHAR) == NULL)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = NULL_CHAR;
		stash = append_to_stash(stash, buf);
		if (stash == NULL)
			break ;
	}
	free(buf);
	return (stash);
}

static char	*prepare_final_line(char **stash)
{
	char	*line;

	if (**stash == NULL_CHAR)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	line = ft_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

static char	*extract_line_from_stash(char **stash)
{
	char	*sep_ptr;
	char	*line;
	char	*rest_of_buffer;

	if (stash == NULL || *stash == NULL)
		return (NULL);
	sep_ptr = ft_strchr(*stash, SEP_CHAR);
	if (sep_ptr == NULL)
		return (prepare_final_line(stash));
	line = ft_substr(*stash, 0, sep_ptr - *stash + SEP_CHAR_ALLOC);
	rest_of_buffer = ft_strdup(SEP_CHAR_ALLOC + sep_ptr);
	free(*stash);
	*stash = rest_of_buffer;
	if (*stash != NULL && **stash == NULL_CHAR)
	{
		free(*stash);
		*stash = NULL;
	}
	if (line == NULL)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + NULL_CHAR_ALLOC);
	if (buf == NULL)
	{
		free(stash);
		return (NULL);
	}
	stash = refill_stash_from_fd(buf, fd, stash);
	if (stash == NULL)
		return (NULL);
	return (extract_line_from_stash(&stash));
}
