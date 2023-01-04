#include "philo.h"

void is_alive(t_data const_data, t_philo *philo)
{
	int eat_time;
	static int control = 0;
	eat_time = philo->eat_time[const_data.philo_n];
	if(const_data.time_to_die < to_usec()-philo->last_eat[const_data.philo_n])
	{
		sem_wait(philo->sem_is_alive);
		philo->is_alive = 0;
		usleep(1000);
		print_sem(const_data,philo,4);
		exit(1);
	}
	if (const_data.argc == 6 && eat_time == \
	const_data.optional && control == 0)
	{
		sem_wait(philo->sem_is_alive);
		philo->eat_time[0] ++;
		printf("EATTİME %p | %i philo %i \n",&philo->eat_time[0],philo->eat_time[0],const_data.philo_n);
		control++;
		if(philo->eat_time[0] == const_data.total_number_of_philo)
			exit(1);
		sem_post(philo->sem_is_alive);
	}
}

int time_divide_five(int time)
{
	int count;
	count = time/5;
	return count;
}

void divide_usleep(t_data const_data, t_philo *philo, int time)
{
	int count = time_divide_five(time);
	while (count--)
	{
		is_alive(const_data,philo);
		usleep(5);
	}
	if (time%5 != 0)
	{
		is_alive(const_data,philo);
		usleep(time%5);
	}
	is_alive(const_data,philo);
}

int	main(int argc, char **argv)
{
	t_data	const_data;
    t_philo philo;
	int nphilo;

	if (arg_control(argc, argv) == 1)
	{
		fill_data_const(&const_data, argv + 1, argc);
        start_forks(const_data, &philo);
	}
	nphilo = 0;
	waitpid(-1, NULL, 0);
	while (const_data.total_number_of_philo>=nphilo)
	{
		kill(philo.pid[nphilo++], SIGINT);
	}
}