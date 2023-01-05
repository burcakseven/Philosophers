#include "philo.h"

void is_alive(t_data const_data, t_philo *philo)
{
	int eat_time;
	eat_time = philo->eat_time[const_data.philo_n];
	if(const_data.time_to_die <= to_usec()-philo->last_eat[const_data.philo_n])
	{
		sem_wait(philo->sem_is_alive);
		philo->is_alive = 0;
		usleep(1000);
		print_sem(const_data,philo,4);
		exit(1);
	}
	if (const_data.argc == 6 && eat_time == const_data.optional)
	{
		exit(1);
	}
}

void divide_usleep(t_data const_data, t_philo *philo, int time,int flag)
{
	long	start;
	int eat_time;

	eat_time = philo->eat_time[const_data.philo_n];
	if(flag == 1 && const_data.argc == 6 && eat_time == const_data.optional )
	{
		usleep(const_data.time_to_eat);
		sem_post(philo->left);
		sem_post(philo->right);
	}
	start = to_usec();
	while (1)
	{
		is_alive(const_data, philo);
		if (to_usec() - start >= time)
			break ;
		usleep(100);
	}
	is_alive(const_data, philo);
}

void wait_and_kill(t_data const_data, t_philo philo)
{
	int nphilo;
	nphilo = 0;
	if(const_data.argc == 5)
	{
		waitpid(-1, NULL, 0);
		while (const_data.total_number_of_philo>=nphilo)
		{
			kill(philo.pid[nphilo++], SIGINT);
		}
	}
	else if(const_data.argc == 6)
	{
		while(nphilo++ < const_data.total_number_of_philo)
		{
			waitpid(philo.pid[nphilo],NULL,0);
		}
		nphilo = 0;
		while (const_data.total_number_of_philo>=nphilo)
			kill(philo.pid[nphilo++], SIGINT);
	
	}
}

int	main(int argc, char **argv)
{
	t_data	const_data;
    t_philo philo;

	if (arg_control(argc, argv) == 1)
	{
		fill_data_const(&const_data, argv + 1, argc);
        start_forks(const_data, &philo);
		wait_and_kill(const_data, philo);
		free(&philo);
	}
}