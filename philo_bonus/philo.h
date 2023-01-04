#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>

typedef struct	s_data
{
    int total_number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int optional;
    int argc;
    int philo_n;
    
}		t_data;

typedef struct	s_philo
{
    sem_t *right;
    sem_t *left;
    sem_t *sem_is_alive;
    sem_t *sem_print;
    int rightnum;
    int leftnum;
    pid_t *pid;
    int is_alive;
    long *last_eat;
    long initial;
    pthread_t thread_catch;
    t_data const_data;
}		t_philo;

//forks.c
void	fill_data_const(t_data *const_data, char **data, int argc);
void	fork_function(sem_t *right, sem_t *left, t_data const_data, t_philo *philo);
void    start_forks(t_data const_data,t_philo *philo);

//philo_behaviour.c
void	philo_eats_even(sem_t *right, sem_t *left, t_data const_data,t_philo *philo);
void philo_sleeps(t_data const_data,t_philo *philo);
void philo_behaviour(sem_t *right,sem_t *left, t_data const_data, t_philo *philo);

//philo.c
void is_alive(t_data const_data, t_philo *philo);
void divide_usleep(t_data const_data, t_philo *philo, int time);
int time_divide_five(int time);

// sem_func.c
void op_sem(t_data const_data,t_philo *philo);
void print_sem(t_data const_data,t_philo *philo, int flag);

//utils.c
int	ft_strlen(char *str);
int	arg_control(int argc, char **argv);
int	ft_atoi(char *str);
long	to_usec(void);
#endif