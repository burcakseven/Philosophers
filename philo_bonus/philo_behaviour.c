#include "philo.h"
void	philo_eats_even(sem_t *right, sem_t *left, t_data const_data,t_philo *philo)
{
if(sem_wait(left)== 0){
	print_sem(const_data,philo,0);

	if(sem_wait(right)== 0){
		print_sem(const_data,philo,0);
		print_sem(const_data,philo,1);
		philo->last_eat[const_data.philo_n] = to_usec();
		divide_usleep(const_data,philo,const_data.time_to_eat);
		sem_post(right);}
		sem_post(left);
}
}

void philo_sleeps(t_data const_data,t_philo *philo)
{
	int difference;
	int l_dif_n;

	l_dif_n = (int)(to_usec() - philo->last_eat[const_data.philo_n]);
	difference = const_data.time_to_eat-const_data.time_to_sleep;
	print_sem(const_data,philo,2);
	if (const_data.time_to_die < l_dif_n +const_data.time_to_sleep)
	{
		usleep(const_data.time_to_die -l_dif_n);
		is_alive(const_data,philo);
	}
	usleep(const_data.time_to_sleep);
	if (const_data.time_to_sleep < const_data.time_to_eat)
	{
		print_sem(const_data,philo,3);
		usleep(difference);
		is_alive(const_data,philo);
	}
	
}

void philo_behaviour(sem_t *right,sem_t *left, t_data const_data, t_philo *philo)
{
	is_alive(const_data,philo);
	philo_eats_even(right,left,const_data,philo);
	is_alive(const_data,philo);
	philo_sleeps(const_data,philo);

}