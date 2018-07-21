#include <stdio.h>


/**
 * Header structure for StatList.
 */
struct StatList {
	/** Actual list head */
	struct List head;
	/** Count of objects currently in list */
	int cur_count;
#ifdef LIST_DEBUG
	/** List name */
	const char *name;
#endif
};

/** Define and initialize StatList head */
#ifdef LIST_DEBUG
#define STATLIST(var) struct StatList var = { {&var.head, &var.head}, 0, #var }
#else
#define STATLIST(var) struct StatList var = { {&var.head, &var.head}, 0 }
#endif

int main(int argc, char *argv[])
{
    STATLIST(my_list);
    return 0;
}
