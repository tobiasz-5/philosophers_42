#include "philosophers.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	first_control(char *argv1)
{
	if (is_digit(argv1) || ft_atoi(argv1) == 0)
	{
		printf("Philos are positive beings\n");
		return(1);
	}
	if (ft_atoi(argv1) > PHILO_MAX)
	{
		printf("Number of Philos must be less or equal 200\n");
		return (1);
	}
	return (0);
}

int wrong_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Choose Five Args or an Optional Sixth\n");
		return (1);
	}
	return (0);
}

int	wrong_contents(char **argv)
{
	if (first_control(argv[1]) == 1)
		return (1);
	if (is_digit(argv[2]) || ft_atoi(argv[2]) == 0)
	{
		printf("No time to die...\n");
		return (1);
	}
	if (is_digit(argv[3]) || ft_atoi(argv[3]) == 0)
	{
		printf("No time to eat...\n");
		return (1);
	}
	if (is_digit(argv[4]) || ft_atoi(argv[4]) == 0)
	{
		printf("No time to sleep...\n");
		return (1);
	}
	if (argv[5] && (is_digit(argv[5]) || ft_atoi(argv[5]) == 0))
	{
		printf("Meals are positive\n");
		return (1);
	}
	return (0);
}


// Data races occur when multiple threads access shared data concurrently and at least one thread modifies the data. 
// Using mutexes correctly can prevent data races by ensuring that only one thread can access the shared data at a time
// init_control(&control, philos); passaggio per riferimento. passo direttamente la struttura originale &
int	main(int argc, char **argv)
{
	t_control		control;
	t_philos		philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	t_set		set;

	if (wrong_args(argc))
		return (1);
	if (wrong_contents(argv))
		return (1);
	init_input(&set, argv);
	init_control(&control, philos);
	init_forks(forks, set.num_of_philos);
	init_philos(philos, &control, forks, &set);
	if(make_threads_then_join(&control, forks))
		return(write(2, "Threads\n", 8), 1);
	if(clean_all(NULL, &control, forks))
		return(write(2, "Error Destroying Mutexes\n", 25), 1);
	printf(END "End of Simulation\n" RESET);
	return (0);
}
// When you run a C program, the operating system creates a single thread to execute the main function.
// This thread is implicitly created by the operating system and is often referred to as the main thread.

