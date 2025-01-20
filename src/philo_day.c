#include "philosophers.h"

void	think(t_philos *philo)
{
	stamp_infos("is thinking", philo, philo->id);
}

void sleeps(t_philos *philo)
{
    stamp_infos("is sleeping", philo, philo->id);
    ft_usleep(philo->set->time_to_sleep);
}


void	solitary_philo(t_philos *philo)
{
	if (philo->set->num_of_philos == 1)
	{
		ft_usleep(philo->set->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
	}
	return;
}

void eat(t_philos *philo)
{
    pthread_mutex_lock(philo->r_fork);
    stamp_infos("has taken a rgt fork", philo, philo->id);
    solitary_philo(philo);
    pthread_mutex_lock(philo->l_fork);
    stamp_infos("has taken a lft fork", philo, philo->id);
    philo->eating = true;
    stamp_infos("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meals);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meals);
    ft_usleep(philo->set->time_to_eat);
    philo->eating = false;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}