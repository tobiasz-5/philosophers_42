#include "philosophers.h"

int	simulation_is_active(t_philos *philo)
{
	pthread_mutex_lock(philo->end);
	if (*philo->end_simulation == true)
	{
		pthread_mutex_unlock(philo->end);
		return (0);
	}
	pthread_mutex_unlock(philo->end);
	return (1);
}

void	*philo_day(void *philo_data)
{
	t_philos	*philo;

	philo = (t_philos *)philo_data;
	if (philo->id % 2)
		ft_usleep(10);
	while (simulation_is_active(philo))
	{
		eat(philo);
		sleeps(philo);
		think(philo);
	}
	return (philo_data);
}

// int pthread_join(pthread_t thread, void **retval);
// 1) The identifier of the thread to be joined
// 2)A pointer to a pointer where the exit status of the joined thread will be stored. This allows the thread that called pthread_join to obtain the return value of the terminated thread.
// If the caller is not interested in the thread’s exit status, retval can be NULL

int make_threads_then_join(t_control *control, pthread_mutex_t *forks)
{
    pthread_t arbiter;
    int i;

    if (pthread_create(&arbiter, NULL, &supervise, control->philos))
        return(clean_all("Creation error:\n", control, forks), 1);
    i = -1;
    while (++i < control->philos[0].set->num_of_philos)
    {
        if (pthread_create(&control->philos[i].thread, NULL, &philo_day,
                           &control->philos[i]))
            return(clean_all("Creation error:\n", control, forks), 1);
    }
	if (pthread_join(arbiter, NULL))                                   //pthread_t invalid_thread = 0; --> if (pthread_join(invalid_thread, NULL)) to make it fail....0 is an invalid thread ID
		return(clean_all("Join error:\n", control, forks), 1);
    i = -1;
    while (++i < control->philos[0].set->num_of_philos)
    {
        if (pthread_join(control->philos[i].thread, NULL))
        	return(clean_all("Join error:\n", control, forks), 1);
    }
    return (0);
}

// Supervise Function:

// The supervise function detects that a philosopher has died (someone_died(philos) == 1) and breaks the loop.
// The supervise function then returns.

// Thread Join:

// In make_threads_then_join, the supervisor thread (arbiter) finishes, and pthread_join(arbiter, NULL) completes successfully.
// The remaining philosopher threads are joined.

// the pthread_join function is used to ensure proper synchronization and clean termination of threads in a multi-threaded program

// Synchronization: pthread_join ensures that the calling thread (usually the main thread) waits for the specified thread to terminate. 
// This helps in synchronizing the termination of threads.

// Using pthread_join ensures that the main thread waits for the other threads to complete before it continues or terminates. 
// This prevents the main thread from terminating prematurely, which would also prematurely end the entire program, possibly leaving other threads unfinished.

// pthread_join also ensures that the resources associated with the thread (such as memory and other resources allocated by the thread) are properly cleaned up.
//  Without joining, resources might remain allocated, leading to memory leaks.

// pthread_join ensures that the main thread waits until each thread has fully completed its execution.