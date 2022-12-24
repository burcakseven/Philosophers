#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct	s_data
{
    int total_number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    
}		t_data;

typedef struct	s_philo
{
    int n;
    int *is_alive;
    int fork_left;
    int for_right;
    t_data  const_data;
    pthread_t thread;
    pthread_mutex_t *mutex;
    long last_eat;
}		t_philo;

//philo.c
void fill_data_const(t_data *const_data, char **data);

//utils.c
int ft_strlen(char *str);
int ft_atoi(char *str);
int arg_control(int argc,char **argv);
long to_usec(void);

//philo_funcs.c
t_philo *create_philo_malloc(t_data const_data);
void fill_each_philo_data(t_philo *all_philo,int number_of_philo);
void *thread_function(void *philo_addres);
void philo_behaviour_odd(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo);
void philo_behaviour_even(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo);

void start_threads(t_philo *philo_address,t_data const_data);
void catch_threads(t_philo *philo_address,int total_number_of_philo);

//behaviour_utils.c
long philo_eats(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo);
void philo_sleeps(t_philo *philo);
void is_dead(long initial, long now, t_philo *philo);

#endif