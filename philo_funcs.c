#include "philo.h"

void philo_behaviour_odd(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    //eat
    philo_eats(mutex_1,mutex_2,philo,&tv);
    gettimeofday(&tv,NULL);
    //sleep
    philo_sleeps(philo);
    gettimeofday(&tv,NULL);
}
void philo_behaviour_even(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
    long static initial = 0;
    struct timeval tv;
    usleep(120);
    gettimeofday(&tv,NULL);
    //eat
    initial = philo_eats(mutex_1,mutex_2,philo,&tv);
    gettimeofday(&tv,NULL);
    is_dead(initial,tv.tv_sec*1000000+tv.tv_usec,philo);
    //sleep
    philo_sleeps(philo);
    gettimeofday(&tv,NULL);
    is_dead(initial,tv.tv_sec*1000000+tv.tv_usec,philo);
}

void *thread_function(void *philo_addres)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    t_philo *philo =(t_philo *)philo_addres;
    pthread_mutex_t *mutex =\
     malloc(sizeof(mutex)*philo->const_data.total_number_of_philo);
    int i = 10;
    while (i)
    {
        if (philo->n%2 == 1)
        {
            philo_behaviour_odd(&mutex[philo->fork_left],&mutex[philo->for_right],philo);
        }
        else
        {
            philo_behaviour_even(&mutex[philo->for_right],&mutex[philo->fork_left],philo);
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
        all_philo[number_of_philo].is_alive = &is_alive;
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