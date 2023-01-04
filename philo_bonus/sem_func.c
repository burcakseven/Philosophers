#include "philo.h"

void op_sem(t_data const_data,t_philo *philo)
{
    sem_unlink("/right");
  	sem_unlink("/left");
	sem_unlink("/alive");
	sem_unlink("/sem_print");

    philo->rightnum = const_data.total_number_of_philo / 2;
    philo->leftnum = philo->rightnum + const_data.total_number_of_philo % 2;


    philo->right = sem_open("/right", O_CREAT | O_EXCL, 0666, philo->rightnum);
    philo->left = sem_open("/left", O_CREAT | O_EXCL, 0666, philo->leftnum);
	philo->sem_is_alive = sem_open("/alive",O_CREAT | O_EXCL, 0666, 1);
	philo->sem_print = sem_open("/alive",O_CREAT | O_EXCL, 0666, 1);
}

void print_sem(t_data const_data,t_philo *philo, int flag)
{
	long time = (to_usec()-philo->initial)/1000;
	sem_wait(philo->sem_print);
	if(flag == 0)
		printf("%li : %i has taken fork \n",time,const_data.philo_n);
	else if(flag == 1)
		printf("%li : %i is eating... \n",time,const_data.philo_n);
	else if(flag == 2)
		printf("%li : philo %i sleeps\n",time,const_data.philo_n);
	else if(flag == 3)
		printf("%li : philo %i thinking\n",time,const_data.philo_n);
	else
		printf("%li : %i is died",time,const_data.philo_n);
	sem_post(philo->sem_print);
}
