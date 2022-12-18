#include "philo.h"
#include "stdio.h"

int ft_strlen(char *str)
{
    int count = 0;
    while (*str++)
    {
        count++;
    }
    return (count);
}
int arg_control(int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        int len = ft_strlen(argv[i]);
        int j = 0;
        while (j < len)
        {
            if (!(48 <= argv[i][j] && argv[i][j] <= 57))
            {
                printf("%s", argv[i]);
                exit(1);
            }
            j++;
        }
        i++;
    }

    return 1;
}

int ft_atoi(char *str) //eksiklikleri var başta kontrol gerekli
{
    int sign = 1;
    long result = 0;
    while (9<= *str && *str <= 13)
    {
        str++;
    }
    if (*str == '-'||*str == '+')
    {
        if (*str++ == '-')
            sign = -1;
    }
    while (*str != '\0')
    {
        result += (*str++ - '0');
        result *= 10;
    }
    return (int)((result/10)*sign);
}