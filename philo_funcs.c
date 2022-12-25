#include "philo.h"

void philo_behaviour_odd(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
    //eat
    if(philo->is_alive){
    philo->last_eat = philo_eats(mutex_1,mutex_2,philo);}
    //sleep
    if(philo->is_alive){
    philo_sleeps(philo);}
    // is_dead(philo->last_eat,to_usec(),philo);
}

void *thread_function(void *philo_addres)
{
    t_philo *philo =(t_philo *)philo_addres;
    pthread_create(&philo->for_live, NULL, &is_dead,philo);//yaşıyor mu kontrol
    // int i = 1;
    while (*philo->is_alive)
    {
        if (philo->n%2 == 1)
        {
            philo_behaviour_odd(&philo->mutex[philo->fork_left],&philo->mutex[philo->for_right],philo);
        }
        else
        {
            philo_behaviour_odd(&philo->mutex[philo->for_right],&philo->mutex[philo->fork_left],philo);
        }
    }
    return philo;
}

void fill_each_philo_data(t_philo *all_philo,int number_of_philo)
{
    int is_alive = 1;
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
        all_philo[number_of_philo].is_alive =  &is_alive;

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