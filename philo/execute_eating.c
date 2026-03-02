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

static void set_start_time(t_philo *philos)
{
	int  i;
	long start_time;

	start_time = time_now_ms();
	i = 0;
	philos->sh->start_time = start_time;
	while (i < philos->sh->n)
	{
		philos[i].last_meal = start_time;
		i++;
	}
}

static int	create_philo(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->sh->n)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			printf("pthread_create() error\n");
			pthread_mutex_unlock(&philos->sh->start_cond_mtx);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	join_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->sh->n)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("pthread_join() error\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int start_simulation(t_philo *philos)
{
	pthread_mutex_lock(&philos->sh->start_cond_mtx);
	set_start_time(philos);
	if (create_philo(philos) != SUCCESS)
		return (FAILURE);
	pthread_mutex_unlock(&philos->sh->start_cond_mtx);
	monitor(philos);
	if (join_philo(philos) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
