#include "philo.h"
void	philo_eats_even(sem_t *right, sem_t *left, t_data const_data,t_philo *philo)
{
	if(sem_wait(left)== 0)
	{
		print_sem(const_data,philo,0);
		if(const_data.total_number_of_philo == 1)
			usleep(const_data.time_to_die);
		is_alive(const_data, philo);
		if(sem_wait(right)== 0)
		{
			print_sem(const_data,philo,0);
			print_sem(const_data,philo,1);
			philo->last_eat[const_data.philo_n] = to_usec();
			philo->eat_time[const_data.philo_n]++;
			divide_usleep(const_data,philo,const_data.time_to_eat,1);
			sem_post(right);
		}
		sem_post(left);
	}
}

void philo_sleeps(t_data const_data,t_philo *philo)
{
	int difference;

	difference = const_data.time_to_eat-const_data.time_to_sleep;
	print_sem(const_data,philo,2);
	divide_usleep(const_data, philo, const_data.time_to_sleep,0);
	if (const_data.time_to_sleep < const_data.time_to_eat)
	{
		print_sem(const_data,philo,3);
		divide_usleep(const_data,philo,difference,0);
	}
}

void philo_behaviour(sem_t *right,sem_t *left, t_data const_data, t_philo *philo)
{
	is_alive(const_data,philo);
	philo_eats_even(right,left,const_data,philo);
	is_alive(const_data,philo);
	philo_sleeps(const_data,philo);

}