/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon.lau <simon.lau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 21:05:49 by simon.lau         #+#    #+#             */
/*   Updated: 2026/10/15 11:45:00 by simon.lau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t		gnl_strlen(const char *s);
char		*gnl_strchr(const char *s, int c);
char		*gnl_strdup(const char *s1);
char		*gnl_substr(const char *s, unsigned int start, size_t len);
char		*gnl_strjoin(char const *s1, char const *s2);
char		*get_next_line(int fd);

#endif
