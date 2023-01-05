#include "philo.h"

void philo_behaviour(pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2, \
t_philo *philo)
{
	if (philo->n % 2 == 1)
		philo_eats_odd(mutex_1, mutex_2, philo);
	else
	{
		philo_eats_even(mutex_2, mutex_1, philo);
	}
	philo_sleeps(philo);
	philo_thinks(philo);
}

void	*thread_function(void *philo_addres)
{
	t_philo	*philo;

	philo = (t_philo *)philo_addres;
	while (1)
	{
		philo_behaviour(&philo->mutex[philo->fork_left], \
		&philo->mutex[philo->for_right], philo);
	}
	return (philo);
}

void	fill_each_philo_data(t_philo *all_philo, \
int number_of_philo)
{
	int	*is_alive;
	int	philo_n;

	philo_n = number_of_philo + 1;
	is_alive = (int *)malloc(sizeof(int) + 1);
	while (1 < philo_n--)
	{
		all_philo[philo_n].n = philo_n;
		all_philo[philo_n].for_right = \
		all_philo[philo_n].n;
		all_philo[philo_n].is_alive = is_alive;
		*all_philo[philo_n].is_alive = 1;
		all_philo[philo_n].eat_time = 0;
		fill_each_philo_two(all_philo, \
		philo_n, number_of_philo);
	}

}

void	fill_each_philo_two(t_philo *all_philo, \
int philo_n, int number_of_philo)
{
	if (all_philo[philo_n].for_right + 1 == \
		number_of_philo)
	{
		all_philo[philo_n].fork_left = \
		(all_philo[philo_n].for_right + 1);
	}
	else
	{
		all_philo[philo_n].fork_left = \
		(all_philo[philo_n].for_right + 1) % number_of_philo;
	}
	if (number_of_philo == 1)
	{
		all_philo[philo_n].fork_left = all_philo[philo_n].for_right;
	}
	
}

t_philo	*create_philo_malloc(t_data const_data)
{
	t_philo	*all_philo;

	all_philo = (t_philo *)malloc(sizeof(t_philo) * \
	(const_data.total_number_of_philo + 1));
	fill_each_philo_data(all_philo, const_data.total_number_of_philo);
	return (all_philo);
}