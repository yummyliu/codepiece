#include "main.h"

typedef struct {
     uint	command;
     pid_t	pid;
     int	slot;
     int	fd;
} my_channel_t;


static void channel_event_handler(my_event_t *ev);
