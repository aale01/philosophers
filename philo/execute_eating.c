/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_eating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:01:44 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/17 13:36:00 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	execute_eating_to_die(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->sh->n)
	{
		pthread_create(philos[i].thread, NULL, routine, &philos[i]);
		// philos[i].last_meal = ft_time();
		philos[i].meals++;
		i++;
	}
}

void	execute_must_eating(t_philo *philos)
{
	(void)philos;
}
