#include "philosophers.h"

// Each philosopher (t_philo instance) points to the same single instance of t_set.
// This means all philosophers share the same seturation data (e.g., num_of_philos, time_to_die, etc.).

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


// il punto (.) per accedere ai membri delle istanze di una struttura. La freccia (->) è usata solo per puntatori a strutture.
// la scelta tra punto (.) e freccia (->) dipende dal fatto che stai lavorando con un'istanza di una struttura o un puntatore a una struttura.
// In the init_philos function, each philosopher (each instance of t_philo) gets a pointer to these mutexes.
// This allows each philosopher to use the same set of mutexes for synchronization
//The dot operator . is used to access members of a structure when you have an instance of the structure.
// The address-of operator & is used to get the address of a variable. The arrow operator -> is used to access members of a structure through a pointer.
// control is a pointer to an instance of the structure t_control.
// To access members of this pointer, you use the arrow operator ->.
// If you have a pointer to a struct, you can use the arrow operator -> to access the members of that struct directly
// philos[i] accesses the i-th element of this array, which is an instance of t_philo.
void	init_philos(t_philos *philos, t_control *control, pthread_mutex_t *forks, t_set *set)
{
	int	i;

	i = -1;
	while (++i < set->num_of_philos)
	{
		philos[i].set = set;  // Assign shared seturation..."Each instance of t_philo has a pointer to a single t_set struct."
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
	pthread_mutex_init(&control->end, NULL); //passaggio per riferimento "&". "->" modifica direttamente il valore
	pthread_mutex_init(&control->meals, NULL); //NULL inizializza il mutex con i valori di default
}
