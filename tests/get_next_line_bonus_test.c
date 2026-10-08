#include "tst.h"
#include "../get_next_line_bonus.h"

tstsuite("get_next_line_bonus")
{
	tstcase("invalid fd returns NULL")
	{
		tstcheck(get_next_line(-1) == NULL, "negative fd must return NULL");
	}

	tstcase("single static variable")
	{
		tstskipif(1)
		{
			/* TODO: verify the implementation keeps a single static
			   variable (e.g. via code inspection alongside this run) */
			tstcheck(0, "placeholder");
		}
	}

	tstcase("multiple fds keep separate state")
	{
		tstskipif(1)
		{
			/* TODO: open several fds, interleave get_next_line() calls
			   across them (fd 3, 4, 5, then repeat) and verify each
			   stream keeps its own state without cross-talk */
			tstcheck(0, "placeholder");
		}
	}
}
