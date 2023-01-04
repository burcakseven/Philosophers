#include "philo.h"
void	philo_eats_even(sem_t *right, sem_t *left, t_data const_data,t_philo *philo)
{
if(sem_wait(left)== 0){
	print_sem(const_data,philo,0);

	if(sem_wait(right)== 0){
		print_sem(const_data,philo,0);
		print_sem(const_data,philo,1);
		philo->last_eat[const_data.philo_n] = to_usec();
		usleep(const_data.time_to_eat);
		sem_post(right);}
		sem_post(left);
}
}

void philo_sleeps(t_data const_data,t_philo *philo)
{
	print_sem(const_data,philo,2);
	usleep(const_data.time_to_sleep);
	if (const_data.time_to_sleep < const_data.time_to_eat)
	{
		print_sem(const_data,philo,3);
		usleep(const_data.time_to_eat-const_data.time_to_sleep);
	}
	
}

void philo_behaviour(sem_t *right,sem_t *left, t_data const_data, t_philo *philo)
{
	philo_eats_even(right,left,const_data,philo);
	philo_sleeps(const_data,philo);

}