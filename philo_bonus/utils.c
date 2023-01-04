#include "philo.h"

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str++)
	{
		count++;
	}
	return (count);
}
int	arg_control(int argc, char **argv)
{
	int	i;
	int	len;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		j = 0;
		while (j < len)
		{
			if (!(48 <= argv[i][j] && argv[i][j] <= 57))
			{
				return (0);
			}
		j++;
		}
	i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	while (9 <= *str && *str <= 13)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
            sign = -1;
        str++;
	}
	while (*str != '\0')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)result * sign);
}

long	to_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}