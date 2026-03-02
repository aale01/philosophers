/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 23:35:09 by abecucci          #+#    #+#             */
/*   Updated: 2026/03/02 18:05:50 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_philo **philos, t_shared *sh)
{
	int	i;

	*philos = (t_philo *)malloc(sh->n * sizeof(t_philo));
	if (!*philos)
		return (FAILURE);
	memset(*philos, 0, sh->n * sizeof(t_philo));
	i = 0;
	while (i < sh->n)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left = i;
		(*philos)[i].right = (sh->n + i - 1) % sh->n;
		(*philos)[i].sh = sh;
		(*philos)[i].meals = 0;
		(*philos)[i].last_meal = 0;
		pthread_mutex_init(&(*philos)[i].last_meal_mtx, NULL);
		i++;
	}
	return (SUCCESS);
}
