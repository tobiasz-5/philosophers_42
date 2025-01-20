#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define PHILO_MAX 200

# define END "\033[1;3;34m"
# define RESET "\033[0m"

typedef struct s_set
{
	int		num_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		max_meals;
}					t_set;

typedef struct s_philos
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	bool			eating;
	bool			*end_simulation;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*stamp;
	pthread_mutex_t	*end;
	pthread_mutex_t	*meals;
	t_set		*set; // Pointer to shared seturation
}					t_philos;

typedef struct s_control
{
	bool			is_dead;
	pthread_mutex_t	end;
	pthread_mutex_t	meals;
	pthread_mutex_t	stamp;
	t_philos			*philos;
}					t_control;

//----------------- Init
void				init_control(t_control *control, t_philos *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philos *philos, t_control *control, pthread_mutex_t *forks, t_set *set);
void				init_input(t_set *set, char **argv);

//----------------- Main functions
int					make_threads_then_join(t_control *control, pthread_mutex_t *forks);
void				*supervise(void *philos_array);
void				*philo_day(void *philo_data);
void				solitary_philo(t_philos *philo);
int					simulation_is_active(t_philos *philo);
int					ate_enough(t_philos *philos);
int					someone_died(t_philos *philos);
int					current_philo_is_dead(t_philos *philo, size_t time_to_die);
void				stamp_infos(char *str, t_philos *philo, int id);

//----------------- Daily routine
void				eat(t_philos *philo);
void				sleeps(t_philos *philo);
void				think(t_philos *philo);

//----------------- Tools
int					first_control(char *argv1);
int					wrong_args(int argc);
int					ft_atoi(char *str);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
int					is_digit(char *str);
int					wrong_contents(char **argv);
size_t				get_time(void);

//----------------- Clean
int					clean_all(char *str, t_control *control, pthread_mutex_t *forks);

#endif
