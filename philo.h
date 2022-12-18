#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"

struct	s_philo
{
    int n;
    int eat_time;
    int sleep_time;
    int think_time;

}		t_philo;

int ft_strlen(char *str);
int ft_atoi(char *str);
int arg_control(int argc,char **argv);

#endif