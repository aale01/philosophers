/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:45:22 by abecucci          #+#    #+#             */
/*   Updated: 2026/03/02 19:46:30 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	time_now_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	// printf("usec: %ld\n", tv.tv_usec);
	// printf("sec: %ld\n", tv.tv_sec);
	// printf("time: %ld\n", tv.tv_sec * 1000000 + tv.tv_usec);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_state(t_philo *p, const char *state)
{
	pthread_mutex_lock(&p->sh->print_mtx);
	printf("%ld %d %s\n", time_now_ms() - p->sh->start_time, p->id, state);
	pthread_mutex_unlock(&p->sh->print_mtx);
}

t_bool	should_stop(t_shared *sh)
{
	t_bool	stop;

	pthread_mutex_lock(&sh->stop_mtx);
	stop = sh->stop;
	pthread_mutex_unlock(&sh->stop_mtx);
	return (stop);
}
