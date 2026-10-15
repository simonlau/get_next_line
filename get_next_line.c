/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon.lau <simon.lau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 21:05:45 by simon.lau         #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by simon.lau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_append(char *stash, char *buf)
{
	char	*tmp;

	tmp = gnl_strjoin(stash, buf);
	free(stash);
	return (tmp);
}

static char	*gnl_refill(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(stash);
		return (NULL);
	}
	while (gnl_strchr(stash, '\n') == NULL)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(stash), NULL);
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		stash = gnl_append(stash, buf);
		if (stash == NULL)
			break ;
	}
	return (free(buf), stash);
}

static char	*gnl_final(char **stash)
{
	char	*line;

	if (**stash == '\0')
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	line = gnl_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

static char	*gnl_drain(char **stash)
{
	char	*nl;
	char	*line;
	char	*rest;

	if (stash == NULL || *stash == NULL)
		return (NULL);
	nl = gnl_strchr(*stash, '\n');
	if (nl == NULL)
		return (gnl_final(stash));
	line = gnl_substr(*stash, 0, (size_t)(nl - *stash + 1));
	rest = gnl_strdup(nl + 1);
	free(*stash);
	*stash = rest;
	if (*stash != NULL && **stash == '\0')
	{
		free(*stash);
		*stash = NULL;
	}
	if (line == NULL)
		return (free(*stash), *stash = NULL, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = gnl_refill(fd, stash);
	if (stash == NULL)
		return (NULL);
	return (gnl_drain(&stash));
}
