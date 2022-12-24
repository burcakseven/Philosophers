#include "philo.h"
// 1 sec == 1000000usec


// long philo_eats(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
// t_philo *philo)
// {
// 	printf("\np:%i------%p-----\n\n",philo->n,mutex_1);
// 	printf("\np:%i------%p-----\n\n",philo->n,mutex_2);
// 	usleep(philo->const_data.time_to_eat);
// 	return 200;
// }

long philo_eats(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
    long temptime = to_usec();
    long temptime2 = 0;
    pthread_mutex_lock(mutex_1);
	printf("\np:%i------%p-----\n\n",philo->n,mutex_1);
	printf("\np:%i------%p-----\n\n",philo->n,mutex_2);
	if (philo->n%2 == 0)
	{
	printf("%li : %i. philosopher has taken %i. fork \n",temptime2,philo->n,philo->for_right);
	}
	else{
	printf("%li : %i. philosopher has taken %i. fork \n",temptime2,philo->n,philo->fork_left);
}
    pthread_mutex_lock(mutex_2);
    temptime2 = to_usec()-temptime;
	if (philo->n%2 == 0)
	{
	printf("%li : %i. philosopher has taken %i. fork \n",to_usec(),philo->n,philo->fork_left);
	}
	else{
    printf("%li : %i. philosopher has taken %i. fork \n",to_usec(),philo->n,philo->for_right);
}
    temptime2 = to_usec()-temptime;
    printf("%li : %i. philosopher is eating \n",temptime2,philo->n);
    temptime2 = to_usec();
    usleep(philo->const_data.time_to_eat);
    pthread_mutex_unlock(mutex_1);
	if (philo->n%2 == 0)
	{
    printf("%li : %i. philosopher has take off %i. fork \n",to_usec(),philo->n,philo->for_right);
	}
	else{
    printf("%li : %i. philosopher has take off %i. fork \n",to_usec(),philo->n,philo->fork_left);
	}
    pthread_mutex_unlock(mutex_2);
    printf("%li : %i. philosopher has take off %i. fork \n",temptime2,philo->n,philo->for_right);
    return (temptime2);
}

void philo_sleeps(t_philo *philo)
{
    printf("sleeping p:%i \n",philo->n);
    usleep(philo->const_data.time_to_sleep);
}
// void philo_thinks(t_philo *philo)
// {
//     struct timeval tv_temp;
//     gettimeofday(&tv_temp,NULL);
//     philo->last_eat-tv_temp*
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
        printf("%li\n",now-initial);
        printf("%i died",philo->n);
        exit(1);
    }
}