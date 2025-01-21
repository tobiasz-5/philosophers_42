#include "philosophers.h"

void	init_input(t_set *set, char **argv)
{
	set->num_of_philos = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat = ft_atoi(argv[3]);
	set->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		set->max_meals = ft_atoi(argv[5]);
	else
		set->max_meals = -1;
}

void	init_philos(t_philos *philos, t_control *control, pthread_mutex_t *forks, t_set *set)
{
	int	i;

	i = -1;
	while (++i < set->num_of_philos)
	{
		philos[i].set = set; 
		philos[i].start_time = get_time();
		philos[i].last_meal = get_time();
		philos[i].id = i + 1;
		philos[i].eating = false;
		philos[i].meals_eaten = 0;
		philos[i].meals = &control->meals;
		philos[i].stamp = &control->stamp;
		philos[i].end = &control->end;
		philos[i].end_simulation = &control->is_dead;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + set->num_of_philos - 1) % set->num_of_philos];
	}
}


// Assegna un mutex ad ogni forchetta. Assegna tanti mutex quante sono le forchette
// *forks e' un puntatore a un array di mutex
// forks è un puntatore al primo elemento dell'array
void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = -1;
	while (++i < philo_num)
		pthread_mutex_init(&forks[i], NULL); // Ottiene l'indirizzo dell'elemento i-esimo dell'array forks.
}

// Assegna il puntatore all'array di filosofi alla struttura control. control->philos = philos;
// t_control *control: puntatore a una struttura t_control, e' il controllo centrale
// t_philo *philos: puntatore a un array di strutture t_philo, sono i filosofi
void	init_control(t_control *control, t_philos *philos)
{
	control->philos = philos;//la struttura control ha ora un riferimento all'array di filosofi.
	control->is_dead = false;
	pthread_mutex_init(&control->stamp, NULL); //mutex garantisce accesso sicuro a variabili condivise tra thread (data race).
	pthread_mutex_init(&control->end, NULL); 
	pthread_mutex_init(&control->meals, NULL); //NULL inizializza il mutex con i valori di default
}
