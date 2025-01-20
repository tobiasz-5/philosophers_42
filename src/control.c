// Understanding Mutexes
// Mutexes Themselves: Mutexes do not have inherent knowledge of which variables they protect. They are simply synchronization primitives that prevent multiple threads from accessing a critical section of code concurrently.

// Purpose of Mutexes: The purpose of a mutex is to ensure that only one thread can execute a particular section of code at a time. This section of code is known as the critical section.

// Critical Section: A critical section is a part of the code where shared resources (variables, data structures, etc.) are accessed or modified.

// How Mutexes Work
// Lock the Mutex: When a thread wants to enter a critical section, it locks the mutex. This action ensures that no other thread can enter the critical section until the mutex is unlocked.

// Execute Critical Section: The thread executes the critical section, where it accesses or modifies shared resources. Because the mutex is locked, no other thread can enter this section and interfere with the operations.

// Unlock the Mutex: Once the thread completes its operations in the critical section, it unlocks the mutex. This action allows other threads to lock the mutex and enter the critical section

#include "philosophers.h"

void	stamp_infos(char *str, t_philos *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->stamp);
	time = get_time() - philo->start_time;
	if (simulation_is_active(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->stamp);
}

int	current_philo_is_dead(t_philos *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meals);
	if (get_time() - philo->last_meal >= time_to_die && philo->eating == false)
	{
		pthread_mutex_unlock(philo->meals);
		return (1);
	}
	pthread_mutex_unlock(philo->meals);
	return (0);
}

int someone_died(t_philos *philos)
{
    int i;

    i = -1;
    while (++i < philos[0].set->num_of_philos)
    {
        if (current_philo_is_dead(&philos[i], philos[i].set->time_to_die))
        {
            stamp_infos("died", &philos[i], philos[i].id);
            pthread_mutex_lock(philos[0].end);
            *philos->end_simulation = true;
            pthread_mutex_unlock(philos[0].end);
            return (1);
        }
    }
    return (0);
}

int ate_enough(t_philos *philos)
{
    int i;
    int finished_eating;

    i = -1;
    finished_eating = 0;
    if (philos[0].set->max_meals == -1)
        return (0);
    while (++i < philos[0].set->num_of_philos)
    {
        pthread_mutex_lock(philos[i].meals);
        if (philos[i].meals_eaten == philos[i].set->max_meals)
            finished_eating++;
        pthread_mutex_unlock(philos[i].meals);
    }
    if (finished_eating == philos[0].set->num_of_philos)
    {
        pthread_mutex_lock(philos[0].end);
        *philos->end_simulation = true;
        pthread_mutex_unlock(philos[0].end);
        return (1);
    }
    return (0);
}

void	*supervise(void *philos_array)
{
	t_philos	*philos;

	philos = (t_philos *)philos_array;
	while (42)
		if (someone_died(philos) == 1 || ate_enough(philos) == 1)
			break ;
	return (philos_array);
}
