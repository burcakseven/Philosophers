#include "philo.h"

void fill_data_const(t_data *const_data, char **data)
{
    const_data->total_number_of_philo = ft_atoi(data[0]);
    const_data->time_to_die = ft_atoi(data[1]);
    const_data->time_to_eat = ft_atoi(data[2]);
    const_data->time_to_sleep = ft_atoi(data[3]);

}

int main(int argc, char **argv)
{
    t_data const_data;

    arg_control(argc, argv);
    fill_data_const(&const_data,argv+1);
    create_philo_malloc(&const_data);
}