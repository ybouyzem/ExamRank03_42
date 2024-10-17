#include "get_next.h"

char    *ft_strdup(char *str)
{
    char *new;
    int i;

    i = 0;
    while (str[i])
        i++;
    new = (char *)malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    char    line[70000];
    static int buffer_read;
    static int buffer_pos;
    int i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        line[i++] = buffer[buffer_pos++];
        if (line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}


int main()
{
    int fd;
    char *line;

    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        printf("Error\n");
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}