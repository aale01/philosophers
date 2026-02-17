/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_eating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:01:44 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/17 18:13:17 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	execute_eating_to_die(t_philo *philos)
{
	int		i;
	// int		stop;
	// long	start_time;

	i = 0;
	// start_time = time_now_us();
	pthread_mutex_lock(&philos->sh->start_mtx);
	while (i < philos->sh->n)
	{
		// philos[i].last_meal = start_time;
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			perror("pthread_create() error");
			pthread_mutex_unlock(&philos->sh->start_mtx);
			return (FAILURE);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->sh->start_mtx);
	// stop = 0;
	// while (!stop)
	// {
	// 	if (time_now_ms() - philos)
	// }
	return (SUCCESS);
}

int	execute_must_eating(t_philo *philos)
{
	(void)philos;
	return (SUCCESS);
}
