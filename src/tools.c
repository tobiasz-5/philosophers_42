#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i]);
	return (i);
}

int	ft_atoi(char *str)
{
	unsigned long long		n;
	int						sign;

	n = 0;
	sign = 1;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (n * sign);
}

int	clean_all(char *str, t_control *control, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	if (str)
	{
		usleep(100);
		write(2, str, ft_strlen(str));
	}
	if (pthread_mutex_destroy(&control->stamp))
		return(1);
	if (pthread_mutex_destroy(&control->meals))
		return(1);
	if (pthread_mutex_destroy(&control->end))
		return(1);
	while (++i < control->philos[0].set->num_of_philos)
	{
		if(pthread_mutex_destroy(&forks[i]))
			return(1);
	}
	return(0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 21);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
