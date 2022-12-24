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
    int i = 0;
    philo_address->mutex = malloc(sizeof(pthread_mutex_t)\
        *(const_data.total_number_of_philo+1));

    while (i < const_data.total_number_of_philo)
    {
        philo_address[i].mutex = philo_address->mutex;
        pthread_mutex_init(philo_address->mutex+i, NULL);
        philo_address[i].const_data = const_data;
        philo_address[i].last_eat = to_usec();
        pthread_create(&philo_address[i].thread, NULL, &thread_function, &philo_address[i]);//fonksiyon oluşturulacak
    i ++;
    }
}

void catch_threads(t_philo *philo_address,int total_number_of_philo)
{
    int i = 0;
    while (i < total_number_of_philo)
    {
        pthread_join(philo_address[i].thread,NULL);
        i++;
    }
    
}

int main(int argc, char **argv)
{
    t_data const_data;
    t_philo *philo_address;
    arg_control(argc, argv);
    fill_data_const(&const_data,argv+1);
    philo_address = create_philo_malloc(const_data);
    start_threads(philo_address,\
    const_data);
    catch_threads(philo_address,const_data.total_number_of_philo);
}