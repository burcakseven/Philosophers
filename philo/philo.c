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

void	start_threads(t_philo *philo_address, t_data const_data)
{
	int	i;

	i = 0;
	philo_address->mutex = malloc(sizeof(pthread_mutex_t) \
	*(const_data.total_number_of_philo + 2));
	while (i <= const_data.total_number_of_philo + 1)
	{
		pthread_mutex_init(&(philo_address->mutex[i]), NULL);
		i++;
	}
	i = 1;
	 long initial = to_usec()/1000;
	while (i <= const_data.total_number_of_philo)
	{
		philo_address[i].mutex = philo_address->mutex;
		philo_address[i].const_data = const_data;
		philo_address[i].last_eat = to_usec();
		philo_address[i].initial = initial;
		usleep(100);
		pthread_create(&philo_address[i].thread, NULL, \
		&thread_function, &philo_address[i]);
		pthread_create(&philo_address[i].for_live, NULL, \
		&is_dead, &philo_address[i]);
		i++;
	}
}

void	catch_threads(t_philo *philo_address, int total_number_of_philo)
{
	int	i;

	i = 1;
	while (i <= total_number_of_philo)
	{
		pthread_join(philo_address[i].for_live, NULL);
		i++;
	}
}

void	malloc_to_free(t_philo *philo_address)
{
	free(philo_address->mutex);
	free(philo_address->is_alive);
	free(philo_address);
}

int	main(int argc, char **argv)
{
	t_data	const_data;
	t_philo	*philo_address;

	if (arg_control(argc, argv) == 1)
	{
		fill_data_const(&const_data, argv + 1, argc);
		philo_address = create_philo_malloc(const_data);
		start_threads(philo_address, \
		const_data);
		catch_threads(philo_address, const_data.total_number_of_philo);
		malloc_to_free(philo_address);
	}
}6