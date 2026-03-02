#include "philosophers.h"

static t_bool	is_dead(t_philo *philo)
{
	int64_t	now;
	t_bool	dead;

	now = time_now_ms();
	pthread_mutex_lock(&philo->last_meal_mtx);
	dead = (now - philo->last_meal > philo->sh->t_die);
	pthread_mutex_unlock(&philo->last_meal_mtx);
	return (dead);
}

static t_bool	reached_meal_count(t_philo *philo)
{
	if (philo->sh->must_eat < 0) //controllare qualcosa qua che non funziona
		return (False);
	return (philo->meals >= philo->sh->must_eat);
}

void	monitor(t_philo *philos)
{
	int		i;
	t_bool	all_philos_full;

	while (!should_stop(philos->sh))
	{
		usleep(MONITOR_SLEEP_TIME_US);
		i = 0;
		all_philos_full = True;
		while (i < philos->sh->n && !should_stop(philos->sh))
		{
			if (is_dead(&philos[i]))
			{
				raise_stop(philos->sh);
				print_state(&philos[i], "died");
				break ;
			}
			if (all_philos_full && !reached_meal_count(&philos[i]))
				all_philos_full = False;
			i++;
		}
		if (all_philos_full)
			raise_stop(philos->sh);
	}
}
