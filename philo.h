#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"


typedef struct	s_philo
{
    int n;
    int is_alive;
    int fork_left;
    int for_right;

}		t_philo;

typedef struct	s_data
{
    int total_number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    
}		t_data;

int ft_strlen(char *str);
int ft_atoi(char *str);
int arg_control(int argc,char **argv);
void fill_data_const(t_data *const_data, char **data);

#endif