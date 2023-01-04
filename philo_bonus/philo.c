#include "philo.h"

void *is_alive(void *phi)
{
	t_philo *philo = (t_philo *)phi;
	int philo_n;
	int time_to_die;

	time_to_die = philo->const_data.time_to_die;
	philo_n = philo->const_data.philo_n;
	if(time_to_die < to_usec()-philo->last_eat[philo_n])
	{
		sem_wait(philo->sem_is_alive);
		philo->is_alive = 0;
		usleep(1000);
		print_sem(philo->const_data,philo,4);
		exit(1);
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	t_data	const_data;
    t_philo philo;
	int nphilo;

	if (arg_control(argc, argv) == 1)
	{
		fill_data_const(&const_data, argv + 1, argc);
		philo.thread_catch = malloc(sizeof(pthread_t)*const_data.total_number_of_philo);
        start_forks(const_data, &philo);
	}
	nphilo = 0;
	wait(NULL);
	while (const_data.total_number_of_philo>=nphilo)
	{
		pthread_join(philo.thread_catch[nphilo],NULL);
		kill(philo.pid[nphilo++], SIGINT);
	}
}