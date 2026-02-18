/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:31:09 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/18 18:23:04 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_shared *sh, t_philo **philos)
{
	int	i;

	if (philos && *philos)
	{
		i = 0;
		while (i < (*philos)->sh->n)
			pthread_mutex_destroy(&(*philos)[i++].meal_mtx);
		free(*philos);
		*philos = NULL;
	}
	if (!sh)
		return ;
	if (sh->forks)
	{
		i = 0;
		while (i < sh->n)
			pthread_mutex_destroy(&sh->forks[i++]);
		free(sh->forks);
		sh->forks = NULL;
	}
	pthread_mutex_destroy(&sh->print_mtx);
	pthread_mutex_destroy(&sh->start_cond_mtx);
	pthread_mutex_destroy(&sh->stop_mtx);
}

int	cleanup_fail(t_shared *sh, t_philo **philos)
{
	cleanup(sh, philos);
	return (EXIT_FAILURE);
}
