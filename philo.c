#include "philo.h"

void fill_data_const(t_data *const_data, char **data)
{
    const_data->total_number_of_philo = ft_atoi(data[0]);
    const_data->time_to_die = ft_atoi(data[1]);
    const_data->time_to_eat = ft_atoi(data[2]);
    const_data->time_to_sleep = ft_atoi(data[3]);

}

void start_threads(t_philo *philo_address,t_data const_data)
{
    int ret;
    int i = 0;
    while (i < const_data.total_number_of_philo)
    {
     ret = pthread_create(&philo_address[i].thread, NULL, &thread_function, &philo_address[i]);//fonksiyon oluşturulacak
     if (ret != 0) {
         exit(1);
     }
    i++;
    }
}

int main(int argc, char **argv)
{
    t_data const_data;

    arg_control(argc, argv);
    fill_data_const(&const_data,argv+1);
    start_threads(create_philo_malloc(const_data),\
    const_data);
    sleep(10);
}