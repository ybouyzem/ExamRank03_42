# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <libc.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

char *get_next_line(int fd);


#endif