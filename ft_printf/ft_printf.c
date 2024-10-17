#include <unistd.h>
#include <stdarg.h>

int printstr(char *s)
{
    int i = 0;
    if (!s)
        s = "(null)";
    while(s[i])
        write(1,&s[i++],1);
    return (i);
}
void printbase(long long n,int base,int *len)
{
    if (n < 0)
    {
        *len += write(1,"-",1);
        n *= -1;
    }
    if (n >= base)
        printbase(n / base,base,len);
    *len += write(1,&"0123456789abcdef"[n % base],1);
}
int ft_printf(const char *s, ... )
{
    int len = 0;
    char c;
    int i = 0;
    va_list ar;

    va_start(ar,s);
    while(s[i])
    {
        if (s[i] == '%' && s[i + 1])
        {
            c = s[i + 1];
            if (c == 's')
                len += printstr(va_arg(ar,char *));
            else if (c == 'd')
                printbase((long long)va_arg(ar,int),10,&len);
            else if (c == 'x')
                printbase((long long)va_arg(ar,unsigned int),16,&len);
            i++;
        }else
        {
            len += write(1,&s[i],1);
        }
        i++;
    }
    va_end(ar);
    return len;
}

#include <stdio.h>
int main()
{
    int r = ft_printf("hello %s, i am %d\n", "world", 21);
    printf("r:  %d\n", r);
}