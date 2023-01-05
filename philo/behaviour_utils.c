#include "philo.h"

void	philo_eats_odd(pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2, \
	t_philo *philo)
{
	pthread_mutex_lock(mutex_1);
	printf("%li :%i has taken a fork.\n",to_usec()/1000-philo->initial,philo->n);

	pthread_mutex_lock(mutex_2);
	printf("%li :%i has taken a fork.\n",to_usec()/1000-philo->initial,philo->n);
	pthread_mutex_lock(&philo->mutex[philo->const_data.total_number_of_philo+1]);
	printf("%li :%i is eating...\n",to_usec()/1000-philo->initial,philo->n);
	philo->eat_time++;
	philo->last_eat = to_usec();
	pthread_mutex_unlock(&philo->mutex[philo->const_data.total_number_of_philo+1]);
	divide_usleep(philo->const_data.time_to_eat);

	pthread_mutex_unlock(mutex_1);
	pthread_mutex_unlock(mutex_2);
}
void philo_eats_even(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
	pthread_mutex_lock(mutex_1);
	printf("%li :%i has taken a fork.\n",to_usec()/1000-philo->initial,philo->n);
	
	pthread_mutex_lock(mutex_2);
	printf("%li :%i has taken a fork.\n",to_usec()/1000-philo->initial,philo->n);

	pthread_mutex_lock(&philo->mutex[philo->const_data.total_number_of_philo+1]);
	printf("%li :%i is eating...\n",to_usec()/1000-philo->initial,philo->n);
	philo->eat_time++;
	philo->last_eat = to_usec();
	pthread_mutex_unlock(&philo->mutex[philo->const_data.total_number_of_philo+1]);

	divide_usleep(philo->const_data.time_to_eat);

	pthread_mutex_unlock(mutex_1);
	pthread_mutex_unlock(mutex_2);
}

void philo_sleeps(t_philo *philo)
{
    printf("%li :%i is sleeping...\n",to_usec()/1000-philo->initial,philo->n);
	divide_usleep(philo->const_data.time_to_sleep);
}

void philo_thinks(t_philo *philo)
{
	printf("%li :%i is thinking...\n",to_usec()/1000-philo->initial,philo->n);
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

int	get_eat(t_philo *philo)
{
	int	ret;
	int last = philo->const_data.total_number_of_philo+1;

	pthread_mutex_lock(&(philo->mutex[last]));
	ret = philo->eat_time;
	pthread_mutex_unlock(&(philo->mutex[last]));
	return (ret);
}

void *is_dead(void *philo_adress)
{
	t_philo *philo =(t_philo *)philo_adress;
	while (die_to_last_eat(philo))
	{
		if (is_alive(philo) == 0|| (philo->const_data.argc\
		 == 6 && get_eat(philo) == philo->const_data.optional))
		{
		pthread_detach(philo->thread);
		return NULL;
}	
	usleep(2000);
}
	pthread_mutex_lock(&philo->mutex[0]);
	if (*(philo->is_alive) == 0)
		{
		pthread_detach(philo->thread);
		pthread_mutex_unlock(&philo->mutex[0]);
		return NULL;
		}
	*philo->is_alive = 0;
	usleep(1000);
	printf("%i died.\n",philo->n);
	pthread_detach(philo->thread);
	pthread_mutex_unlock(&philo->mutex[0]);
	return philo;
}