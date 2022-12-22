#include "philo.h"

void philo_behaviour(pthread_mutex_t *mutex_1,pthread_mutex_t *mutex_2,\
t_philo *philo)
{
    pthread_mutex_lock(mutex_1);
    printf("p:%i ,fork : %i \n",philo->n,philo->fork_left);
    pthread_mutex_lock(mutex_2);
    printf("p:%i ,fork : %i \n",philo->n,philo->for_right);
    printf("eat:%i \n",philo->n);
    
    pthread_mutex_unlock(mutex_1);
    pthread_mutex_unlock(mutex_2);
}

void *thread_function(void *philo_addres)
{
    t_philo *philo =(t_philo *)philo_addres;
    pthread_mutex_t *mutex =\
     malloc(sizeof(mutex)*philo->const_data.total_number_of_philo);
    int i = 1;
    while (i--)
    {
        if (philo->n %2 == 1)
        {
            philo_behaviour(&mutex[philo->fork_left],&mutex[philo->for_right],philo);
        }
        else
        {
            philo_behaviour(&mutex[philo->for_right],&mutex[philo->fork_left],philo);
        }
    }
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