#include "../get_next_line.h"
#include "tst.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WRITE_END 1
#define READ_END 0

static int	make_pipe(const char *s)
{
	int	pipefd[2];
	size_t	len;

	if (pipe(pipefd) == -1)
		return (-1);
	len = strlen(s);
	if (len > 0)
		write(pipefd[WRITE_END], s, len);
	close(pipefd[WRITE_END]);
	return (pipefd[READ_END]);
}

tstsuite("get_next_line")
{
	char	*line;
	int		fd;

	tstcase("invalid fd returns NULL")
	{
		tstexpect(get_next_line(-1) == NULL, "negative fd must return NULL");
		tstexpect(get_next_line(4242) == NULL, "closed fd must return NULL");
	}
	tstcase("empty input drains to NULL")
	{
		fd = open("tests/empty.txt", O_RDONLY);
		tstassert(fd >= 0, "open empty.txt");
		line = get_next_line(fd);
		tstexpect(line == NULL, "empty stash must return NULL");
		close(fd);
	}
	tstcase("single line without newline")
	{
		fd = make_pipe("hello");
		tstassert(fd >= 0, "pipe ready");
		line = get_next_line(fd);
		tstassert(line != NULL, "line not NULL");
		tstexpect(strcmp(line, "hello") == 0, "got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstexpect(line == NULL, "EOF after fragment must be NULL");
		close(fd);
	}
	tstcase("single line with newline")
	{
		fd = make_pipe("hello\n");
		line = get_next_line(fd);
		tstassert(line != NULL, "line not NULL");
		tstexpect(strcmp(line, "hello\n") == 0, "got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstexpect(line == NULL, "EOF must be NULL");
		close(fd);
	}
	tstcase("multi-line drain")
	{
		fd = make_pipe("a\nb\nc\n");
		line = get_next_line(fd);
		tstassert(line != NULL, "line1");
		tstexpect(strcmp(line, "a\n") == 0, "line1 got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstassert(line != NULL, "line2");
		tstexpect(strcmp(line, "b\n") == 0, "line2 got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstassert(line != NULL, "line3");
		tstexpect(strcmp(line, "c\n") == 0, "line3 got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstexpect(line == NULL, "EOF must be NULL");
		close(fd);
	}
	tstcase("final fragment without newline")
	{
		fd = make_pipe("x\ny");
		line = get_next_line(fd);
		tstassert(line != NULL, "line1");
		tstexpect(strcmp(line, "x\n") == 0, "line1 got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstassert(line != NULL, "fragment");
		tstexpect(strcmp(line, "y") == 0, "fragment got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstexpect(line == NULL, "EOF must be NULL");
		close(fd);
	}
	tstcase("long line spans refills")
	{
		fd = make_pipe("0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ\ntail\n");
		line = get_next_line(fd);
		tstassert(line != NULL, "long line");
		tstexpect(strcmp(line, "0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ0123456789ABCDEFGHIJ\n")
			== 0, "long got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstassert(line != NULL, "tail");
		tstexpect(strcmp(line, "tail\n") == 0, "tail got '%s'", line);
		free(line);
		line = get_next_line(fd);
		tstexpect(line == NULL, "EOF must be NULL");
		close(fd);
	}
	tstcase("NULL after EOF stays NULL")
	{
		fd = make_pipe("one\n");
		line = get_next_line(fd);
		tstassert(line != NULL, "line");
		free(line);
		line = get_next_line(fd);
		tstexpect(line == NULL, "first EOF NULL");
		line = get_next_line(fd);
		tstexpect(line == NULL, "second EOF still NULL");
		close(fd);
	}
}
