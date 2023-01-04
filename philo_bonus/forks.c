#include "philo.h"
void	fill_data_const(t_data *const_data, char **data, int argc)
{
	const_data->total_number_of_philo = ft_atoi(data[0]);
	const_data->time_to_die = ft_atoi(data[1]) * 1000;
	const_data->time_to_eat = ft_atoi(data[2]) * 1000;
	const_data->time_to_sleep = ft_atoi(data[3]) * 1000;
	if (argc == 6)
		const_data->optional = ft_atoi(data[4]);
	const_data->argc = argc;
}

void	fork_function(sem_t *right, sem_t *left, t_data const_data, t_philo *philo)
{
	while (philo->is_alive)
	{
		philo_behaviour(right,left,const_data,philo);
	}
	// exit(5);
}

void start_forks(t_data const_data,t_philo *philo)
{
    int nphilo;
	
	philo->is_alive = 1;
	philo->initial = to_usec();
	philo->last_eat = (long *)malloc(sizeof(long)*const_data.total_number_of_philo);
	philo->pid = malloc(sizeof(pid_t)*const_data.total_number_of_philo);
	nphilo = 0;
    op_sem(const_data, philo);

    while (nphilo++<const_data.total_number_of_philo)
	{
		int res= fork();
        if (res == 0)
		{
			const_data.eat_time = 0;
			const_data.philo_n = nphilo;
			philo->last_eat[const_data.philo_n] = to_usec();
            fork_function(philo->right,philo->left,const_data,philo);
			exit(5);
		}
		philo->pid[const_data.total_number_of_philo - nphilo] = res;
	}
}
