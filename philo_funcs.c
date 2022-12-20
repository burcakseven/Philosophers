#include "philo.h"

void *thread_function(void *philo_addres)
{
    t_philo *philo = (t_philo *)philo_addres;
    printf("%i",philo->n);
    return philo;
}

void fill_each_philo_data(t_philo *all_philo,int number_of_philo)
{
    int const_num = number_of_philo;
    while (number_of_philo--)
    {
        all_philo[number_of_philo].n = number_of_philo+1;
        
        all_philo[number_of_philo].for_right =\
         all_philo[number_of_philo].n;

        if (all_philo[number_of_philo].for_right+1 ==\
        const_num)
        {
         all_philo[number_of_philo].fork_left =\
        (all_philo[number_of_philo].for_right+1);
        }
        else
        {
        all_philo[number_of_philo].fork_left =\
        (all_philo[number_of_philo].for_right+1) % const_num;
        }
        all_philo[number_of_philo].is_alive = 1;
    }
    
}

t_philo *create_philo_malloc(t_data const_data)
{
    t_philo *all_philo;
    all_philo = (t_philo *)malloc(sizeof(t_philo)* \
    const_data.total_number_of_philo);
    if (all_philo == NULL)
        exit(1);
    fill_each_philo_data(all_philo,const_data.total_number_of_philo);
    return all_philo;
}