/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_eating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:01:44 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/18 18:20:11 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor(t_philo *philos)
{
	int			i;
	int			dead_id;
	int64_t		dead_time;
	int64_t		now;

	while (1)
	{
		dead_id = -1;
		now = time_now_ms();
		pthread_mutex_lock(&philos->sh->stop_mtx);
		if (philos->sh->stop)
		{
			pthread_mutex_unlock(&philos->sh->stop_mtx);
			break ;
		}
		pthread_mutex_unlock(&philos->sh->stop_mtx);
		i = 0;
		while (i < philos->sh->n)
		{
			pthread_mutex_lock(&philos[i].meal_mtx);
			if (now - philos[i].last_meal > philos->sh->t_die)
			{
				pthread_mutex_unlock(&philos[i].meal_mtx);
				pthread_mutex_lock(&philos->sh->stop_mtx);
				philos->sh->stop = 1;
				pthread_mutex_unlock(&philos->sh->stop_mtx);
				dead_id = philos[i].id;
				dead_time = now;
				break ;
			}
			pthread_mutex_unlock(&philos[i].meal_mtx);
			i++;
		}
		if (dead_id != -1)
		{
			pthread_mutex_lock(&philos->sh->print_mtx);
			printf("%ld %d died\n", dead_time, dead_id);
			pthread_mutex_unlock(&philos->sh->print_mtx);
			break ;
		}
		usleep(1000);
	}
}

int	execute_eating_to_die(t_philo *philos)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&philos->sh->start_cond_mtx);
	while (i < philos->sh->n)
	{
		// philos[i].last_meal = start_time;
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
