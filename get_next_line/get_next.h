#ifndef GET_NEXT_H
# define GET_NEXT_H

#include <unistd.h>
#include <stdlib.h>
#include <libc.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

char *get_next_line(int fd);

#endif