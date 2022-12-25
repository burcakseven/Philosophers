#include "philo.h"
// 1 sec == 1000000usec
long philo_eats(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
	printf("%i\n",philo->n);
	pthread_mutex_lock(mutex_1);
	pthread_mutex_lock(mutex_2);
	usleep(philo->const_data.time_to_eat*1000);
	printf("eat: %i\n",philo->n);

	pthread_mutex_unlock(mutex_1);
	pthread_mutex_unlock(mutex_2);
	printf("unmutex 2: %i\n",philo->n);
	return 200;
}

void philo_sleeps(t_philo *philo)
{
    printf("sleeping p:%i \n",philo->n);
    usleep(philo->const_data.time_to_sleep*1000);
}

// void philo_thinks(t_philo *philo)
// {
//     struct timeval tv_temp;
//     gettimeofday(&tv_temp,NULL);
//     philo->last_eat-tv_temp*
// }

void *is_dead(void *philo_adress)
{
	t_philo *philo =(t_philo *)philo_adress;
	int i = 1;
	while (i)
	{
		if(philo->is_alive == 0)
		{
			pthread_mutex_destroy(&philo->mutex[philo->for_right]);
			i = 0;
		}
		if(to_usec()-philo->last_eat >= philo->const_data.time_to_die*1000)
		{
			pthread_mutex_lock(&philo->mutex[0]);
			*(philo->is_alive) = 0;
			printf("%i died",philo->n);
			pthread_mutex_unlock(&philo->mutex[0]);
			pthread_mutex_destroy(&philo->mutex[philo->for_right]);
			i = 0;
		}
	}
	return (void *)(&philo->n);
}