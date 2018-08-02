#include <stdio.h>

typedef struct table
{
    const char *name;
    const char *create_sql;
}table;

typedef struct worktable
{
	const char *schema;
	const table ts[3];
} worktable;

worktable wt = {"commander",{{"db_info","create table if not exist db_info()"},\
                            {"table_info","create table if not exist table_info"},\
                            {"func_info","create table if not exist func_info"}}};

int main(int argc, char *argv[])
{
    for (int i = 0; i < (sizeof(wt.ts)/sizeof(table)); ++i) {
        printf("%s\n", wt.ts[i].name);
        printf("%s\n", wt.ts[i].create_sql);
        printf("---\n");
    }
    return 0;
}
