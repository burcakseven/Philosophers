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
	printf("last %li\n",philo->last_eat);
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

int is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex[0]);
	if (*(philo->is_alive) == 0)
		{
		pthread_detach(philo->thread);
		pthread_mutex_unlock(&philo->mutex[0]);
		return 0;
		}
	pthread_mutex_unlock(&philo->mutex[0]);
	return 1;
}

int die_to_last_eat(t_philo *philo)
{
	int last = philo->const_data.total_number_of_philo+1;
	pthread_mutex_lock(&philo->mutex[last]);
	if((to_usec()-philo->last_eat) < philo->const_data.time_to_die)
	{
		pthread_mutex_unlock(&philo->mutex[last]);
		return 1;
	}
	pthread_mutex_unlock(&philo->mutex[last]);
	return 0;
}

void *is_dead(void *philo_adress)
{
	t_philo *philo =(t_philo *)philo_adress;
	while (die_to_last_eat(philo))
	{
		usleep(100);
		if (is_alive(philo) == 0)
			return NULL;
	}
	// pthread_mutex_lock(&philo->mutex[0]);
	if (is_alive(philo) == 0)
		return NULL;
	usleep(100);
	*philo->is_alive = 0;
	printf("!!!!!!%i died\n",philo->n);
	pthread_detach(philo->thread);
	// pthread_mutex_unlock(&philo->mutex[0]);
	return philo;
}