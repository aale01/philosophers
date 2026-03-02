/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_eating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:01:44 by abecucci          #+#    #+#             */
/*   Updated: 2026/03/02 19:26:20 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	monitor(t_philo *philos)
{
	int			i;
	int64_t		now;

	while (!should_stop(philos->sh))
	{
		now = time_now_ms();
		i = 0;
		while (i < philos->sh->n)
		{
			pthread_mutex_lock(&philos[i].meal_mtx);
			if (now - philos[i].last_meal > philos->sh->t_die)
			{
				pthread_mutex_unlock(&philos[i].meal_mtx);
				pthread_mutex_lock(&philos->sh->stop_mtx);
				philos->sh->stop = True;
				pthread_mutex_unlock(&philos->sh->stop_mtx);
				print_state(&philos[i], "died");
				break ;
			}
			pthread_mutex_unlock(&philos[i].meal_mtx);
			i++;
		}
		usleep(MONITOR_SLEEP_TIME_US);
	}
}

static void	set_start_time(t_philo *philos)
{
	int		i;
	long	start_time;

	start_time = time_now_ms();
	i = 0;
	philos->sh->start_time = start_time;
	while (i < philos->sh->n)
	{
		philos[i].last_meal = start_time;
		i++;
	}
}

int	execute_eating_to_die(t_philo *philos)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&philos->sh->start_cond_mtx);
	set_start_time(philos);
	while (i < philos->sh->n)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			printf("pthread_create() error");
			pthread_mutex_unlock(&philos->sh->start_cond_mtx);
			return (FAILURE);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->sh->start_cond_mtx);
	monitor(philos);
	i = 0;
	while (i < philos->sh->n)
		if (pthread_join(philos[i++].thread, NULL) != 0)
		{
			printf("pthread_join() error");
			return (FAILURE);
		}
	return (SUCCESS);
}

int	execute_must_eating(t_philo *philos)
{
	(void)philos;
	return (SUCCESS);
}
