#include "philo.h"
// 1 sec == 1000000usec
long philo_eats(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo,struct timeval *tv)
{
    long temptime = tv->tv_sec*1000000+tv->tv_usec;
    long temptime2 = 0;
    pthread_mutex_lock(mutex_1);
    gettimeofday(tv,NULL);
    printf("%li : %i. philosopher has taken %i. fork \n",temptime2,philo->n,philo->fork_left);
    pthread_mutex_lock(mutex_2);
    gettimeofday(tv,NULL);
    temptime2 = tv->tv_sec*1000000+tv->tv_usec-temptime;
    printf("%li : %i. philosopher has taken %i. fork \n",temptime2,philo->n,philo->for_right);
    gettimeofday(tv,NULL);
    temptime2 = (tv->tv_sec*1000000+tv->tv_usec )-temptime;
    printf("%li : %i. philosopher is eating \n",temptime2,philo->n);
    usleep(philo->const_data.time_to_eat);
    pthread_mutex_unlock(mutex_1);
    pthread_mutex_unlock(mutex_2);
    gettimeofday(tv,NULL);
    return (temptime2+temptime);
}

void philo_sleeps(t_philo *philo)
{
    printf("sleeping p:%i \n",philo->n);
    usleep(philo->const_data.time_to_sleep);
}
// void philo_thinks(t_philo *philo)
// {

// }

void is_dead(long initial, long now, t_philo *philo)
{
    if (philo->is_alive == 0)
    {
        exit(1);
    }
    
    if (now-initial > philo->const_data.time_to_die)
    {
        *(philo->is_alive) = 0;
        printf("%i died",philo->n);
        exit(1);
    }
}