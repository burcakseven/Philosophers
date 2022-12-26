#include "philo.h"
// 1 sec == 1000000usec
void philo_eats_odd(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
	printf("%i\n",philo->n);
	pthread_mutex_lock(mutex_1);
	printf("p:%i taken fork:%i\n",philo->n,philo->fork_left);

	pthread_mutex_lock(mutex_2);
	printf("p:%i taken fork:%i\n",philo->n,philo->for_right);
	philo->last_eat = to_usec();
	usleep(philo->const_data.time_to_eat);
	printf("eat: %i \n",philo->n);

	pthread_mutex_unlock(mutex_1);
	printf("p:%i take off fork:%i\n",philo->n,philo->fork_left);

	pthread_mutex_unlock(mutex_2);
	printf("p::%i take off fork:%i\n",philo->n,philo->for_right);
	// printf("unmutex 2: %i\n",philo->n);
}
void philo_eats_even(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
	printf("%i\n",philo->n);
	pthread_mutex_lock(mutex_1);
	printf("p:%i taken fork:%i\n",philo->n,philo->for_right);
	
	pthread_mutex_lock(mutex_2);
	printf("p:%i taken fork:%i\n",philo->n,philo->fork_left);

	philo->last_eat = to_usec();
	usleep(philo->const_data.time_to_eat);
	printf("\neat: %i \n",philo->n);

	pthread_mutex_unlock(mutex_1);
	printf("p:%i take off fork:%i\n",philo->n,philo->for_right);

	pthread_mutex_unlock(mutex_2);
	printf("p:%i take off fork:%i\n",philo->n,philo->fork_left);
}

void philo_sleeps(t_philo *philo)
{
    printf("sleeping p:%i \n",philo->n);
    usleep(philo->const_data.time_to_sleep);
}

void philo_thinks(t_philo *philo,long initial)
{
	long try = to_usec()-initial-philo->const_data.time_to_eat-philo->const_data.time_to_sleep;
	printf("thinking %i /%li\n",philo->n,try);
	usleep(try);
}

void *is_dead(void *philo_adress)
{
	t_philo *philo =(t_philo *)philo_adress;
	int i = philo->const_data.total_number_of_philo;
	while (philo->is_alive[philo->n])
	{
		printf("MEHRABA");
		pthread_mutex_lock(&philo->mutex[0]);
		if(to_usec()-philo->last_eat >= philo->const_data.time_to_die &&philo->is_alive[philo->n] != 0)
		{
			while (i)
			{
				philo->is_alive[i] = 0;
				i--;
			}
			printf("%i died",philo->n);
			i = 0;
		}
		pthread_mutex_unlock(&philo->mutex[0]);
	}
	return philo;
}