#include "philo.h"
// 1 sec == 1000000usec
int philo_eats(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo,struct timeval *tv)
{
    pthread_mutex_lock(mutex_1);
    printf("p:%i ,fork : %i \n",philo->n,philo->fork_left);
    pthread_mutex_lock(mutex_2);
    gettimeofday(tv,NULL);
    printf("p:%i SEC: %li\n",philo->n,tv->tv_sec);
    printf("%i USEC: %i\n",philo->n,tv->tv_usec);
    printf("p:%i ,fork : %i \n",philo->n,philo->for_right);
    printf("eat:%i \n",philo->n);
    sleep(philo->const_data.time_to_eat);
    pthread_mutex_unlock(mutex_1);
    pthread_mutex_unlock(mutex_2);
    return 1;
}

void philo_sleeps(t_philo *philo)
{
    sleep(philo->const_data.time_to_sleep);
}