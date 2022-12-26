#include "philo.h"

void philo_behaviour(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
    //eat
    if(philo->n%2== 1)
        philo_eats_odd(mutex_1,mutex_2,philo);
    else
    {
        philo_eats_even(mutex_2,mutex_1,philo);
    }
    //sleep
    philo_sleeps(philo);
    // philo_thinks(philo,initial);
}

void *thread_function(void *philo_addres)
{
    t_philo *philo =(t_philo *)philo_addres;
    while (1)
    {
            philo_behaviour(&philo->mutex[philo->fork_left],&philo->mutex[philo->for_right],philo);
    }
    return philo;
}
// void fill_threads_pointer(t_philo *all_philo)
// {
//     int number = all_philo->const_data.total_number_of_philo;

//     pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t)*\
//     all_philo->const_data.total_number_of_philo);

//     pthread_t *for_live = (pthread_t *)malloc(sizeof(pthread_t)*\
//     all_philo->const_data.total_number_of_philo);

//     while (1<=number)
//     {
//         all_philo[number].thread = thread;
//         all_philo[number].for_live = for_live;
//     }
       
// }

void fill_each_philo_data(t_philo *all_philo,int number_of_philo)
{
    int philo_n = number_of_philo+1;
    while (1<philo_n--)
    {
        all_philo[philo_n].n = philo_n;
        
        all_philo[philo_n].for_right =\
         all_philo[philo_n].n;

        if (all_philo[philo_n].for_right+1 ==\
        number_of_philo)
        {
         all_philo[philo_n].fork_left =\
        (all_philo[philo_n].for_right+1);
        }
        else
        {
        all_philo[philo_n].fork_left =\
        (all_philo[philo_n].for_right+1) % number_of_philo;
        }
        // all_philo[philo_n].is_alive = all_philo[1].is_alive;
        // all_philo[philo_n].is_alive[philo_n]= 1;
    }
    
}

t_philo *create_philo_malloc(t_data const_data)
{
    t_philo *all_philo;
    all_philo = (t_philo *)malloc(sizeof(t_philo)* \
    (const_data.total_number_of_philo+1));
    if (all_philo == NULL)
        exit(1);
    fill_each_philo_data(all_philo,const_data.total_number_of_philo);
    return all_philo;
}