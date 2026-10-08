#include "tst.h"
#include "../get_next_line.h"

tstsuite("get_next_line")
{
	tstcase("invalid fd returns NULL")
	{
		tstcheck(get_next_line(-1) == NULL, "negative fd must return NULL");
	}

	tstcase("read regular file")
	{
		tstskipif(1)
		{
			/* TODO: open a text file, loop get_next_line() until NULL,
			   check each line keeps its terminating '\n' (except a
			   final unterminated line), free every returned line */
			tstcheck(0, "placeholder");
		}
	}

	tstcase("read from stdin")
	{
		tstskipif(1)
		{
			/* TODO: pipe input on stdin, verify get_next_line(0)
			   returns it one line at a time */
			tstcheck(0, "placeholder");
		}
	}

	tstcase("empty and very long lines")
	{
		tstskipif(1)
		{
			/* TODO: empty file (expect NULL immediately), empty lines
			   (expect "\n"), lines much longer than BUFFER_SIZE */
			tstcheck(0, "placeholder");
		}
	}
}
