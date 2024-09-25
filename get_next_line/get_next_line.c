#include "get_next_line.h"

//  cc -Wall -Wextra -Werror -D BUFFER_SIZE get_next_line.c

int ft_strlen(char *s)
{
    if (!s)
        return 0;
    int i = 0;
    while (s[i])
        i++;
    return i;
}
void ft_strcpy(char *s1, char *s2)
{
    int i = 0;
    while (s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = 0;
}
char *freememory(char *s1, char *s2)
{
    if (s1 != NULL)
        free(s1);
    if (s2 != NULL)
        free(s2);
    return (NULL);
}
int check(char *s)
{
    int i = 0;
    if (!s)
        return i;
    while (s[i])
    {
        if (s[i++] == '\n')
            return 1;
    }
    return 0;
}
char *join_line(char *s1, char *s2)
{
    if (!s1)
    {
        char *str = (char *)malloc(ft_strlen(s2) + 1);
        ft_strcpy(str, s2);
        return str;
    }
    if (!s2)
    {
        char *str = (char *)malloc(ft_strlen(s1) + 1);
        ft_strcpy(str, s1);
        return str;
    }
    int len = ft_strlen(s1);
    int len1 = ft_strlen(s2) + 1;
    char *str = (char *)malloc(len + len1);
    ft_strcpy(str, s1);
    ft_strcpy((str + len), s2);
    free(s1);
    return str;
}
char *rest_line(char *s)
{
    int i = 0;
    int j = 0;

    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    if (s[i] == 0)
        return (free(s), NULL);
    while (s[i + j])
        j++;
    char *str = (char *)malloc(j + 1);
    j = 0;
    while (s[i])
        str[j++] = s[i++];
    str[j] = 0;
    free(s);
    return (str);
}
char *get_line_new(char *s)
{
    int i = 0;
    if (!s)
        return NULL;
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    char *str = (char *)malloc(i + 1);
    i = 0;
    while (s[i])
    {
        str[i] = s[i];
        if (s[i] == '\n')
        {
            i++;
            break;
        }
        i++;
    }
    str[i] = 0;
    return (str);
}
char *read_line(char *s, int fd)
{
    char *buf = NULL;
    int r = 1;
    char *str = (char *)malloc((size_t)BUFFER_SIZE + 1);
    while (r > 0)
    {
        r = read(fd, str, BUFFER_SIZE);
        if (r < 0)
            return (freememory(str, buf));
        str[r] = 0;
        buf = join_line(buf, str);
        if (!buf || buf[0] == 0)
            return (freememory(str, buf), s);
        if (check(buf) || r == 0)
            break;
    }
    free(str);
    str = join_line(s, buf);
    free(buf);
    return str;
}
char *get_next_line(int fd)
{
    static char *rest;
    if (fd < 0 || BUFFER_SIZE < 0)
        return NULL;
    rest = read_line(rest, fd);
    if (!rest || rest[0] == 0)
        return (freememory(rest, NULL));
    char *line = NULL;
    line = get_line_new(rest);
    rest = rest_line(rest);
    return (line);
}