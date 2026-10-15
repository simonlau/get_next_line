/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon.lau <simon.lau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 21:05:40 by simon.lau         #+#    #+#             */
/*   Updated: 2026/10/15 11:45:00 by simon.lau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*gnl_strchr(const char *s, int c)
{
	char	*pos;
	char	target;

	if (s == NULL)
		return (NULL);
	target = (char)c;
	pos = (char *)s;
	while (*pos)
	{
		if (*pos == target)
			return (pos);
		pos++;
	}
	if (*pos == target)
		return (pos);
	return (NULL);
}

char	*gnl_strdup(const char *s1)
{
	size_t	len;
	char	*result;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = gnl_strlen(s1) + 1;
	result = malloc(len * sizeof(*result));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s1[i];
		i++;
	}
	return (result);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*result;
	size_t	i;

	if (s == NULL)
		return (gnl_strdup(""));
	s_len = gnl_strlen(s);
	if (s_len == 0 || start > s_len)
		return (gnl_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	result = malloc((1 + len) * sizeof(*result));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	size_t	i;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	result = malloc((1 + s1_len + s2_len) * sizeof(*result));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len + s2_len)
	{
		if (i < s1_len)
			result[i] = s1[i];
		else
			result[i] = s2[i - s1_len];
		i++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}
