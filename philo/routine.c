/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:25:49 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/17 18:49:11 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	(void)p;
	pthread_mutex_lock(&p->sh->start_mtx);
	pthread_mutex_unlock(&p->sh->start_mtx);
	pthread_mutex_lock(&p->sh->state_mtx);
	p->last_meal = time_now_ms();
	pthread_mutex_unlock(&p->sh->state_mtx);
	// ... loop filosofo ...
	return (NULL);
}