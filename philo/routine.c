/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:25:49 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/18 16:59:42 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *p, const char *state)
{
	pthread_mutex_lock(&p->sh->print_mtx);
	printf("%ld %d %s\n", time_now_ms(), p->id, state);
	pthread_mutex_unlock(&p->sh->print_mtx);
}

static int should_stop(t_philo *p)
{
	int64_t	now;

	now = time_now_ms();
	pthread_mutex_lock(&p->sh->stop_mtx);
	if (p->sh->stop)
	{
		pthread_mutex_unlock(&p->sh->stop_mtx);
		return (1);
	}
	pthread_mutex_unlock(&p->sh->stop_mtx);
	pthread_mutex_lock(&p->meal_mtx);
	if (now - p->last_meal > p->sh->t_die)
	{
		pthread_mutex_unlock(&p->meal_mtx);
		pthread_mutex_lock(&p->sh->stop_mtx);
		p->sh->stop = 1;
		pthread_mutex_unlock(&p->sh->stop_mtx);
		pthread_mutex_lock(&p->sh->print_mtx);
		printf("%ld %d died\n", now, p->id);
		pthread_mutex_unlock(&p->sh->print_mtx);
		return (1);
	}
	pthread_mutex_unlock(&p->meal_mtx);
	return (0);
}

static int	fork_taken(t_philo *p, int fork)
{
	pthread_mutex_lock(&p->sh->forks[fork]);
	if (should_stop(p))
	{
		pthread_mutex_unlock(&p->sh->forks[fork]);
		return (0);
	}
	print_state(p, "has taken a fork");
	return (1);
}

static void	philosophers_loop(t_philo *p)
{
	while (!should_stop(p))
	{
		if (!fork_taken(p, p->left))
			break ;
		if (!fork_taken(p, p->right))
		{
			pthread_mutex_unlock(&p->sh->forks[p->left]);
			break ;
		}
		pthread_mutex_lock(&p->meal_mtx);
		p->last_meal = time_now_ms();
		pthread_mutex_unlock(&p->meal_mtx);
		print_state(p, "is eating");
		usleep(p->sh->t_eat * 1000);
		p->meals++;
		pthread_mutex_unlock(&p->sh->forks[p->right]);
		pthread_mutex_unlock(&p->sh->forks[p->left]);
		if (should_stop(p))
			break ;
		print_state(p, "is sleeping");
		usleep(p->sh->t_sleep * 1000);
		if (should_stop(p))
			break ;
		print_state(p, "is thinking");
	}
}

void *routine(void *arg)
{
	t_philo *p;

	p = (t_philo *) arg;
	pthread_mutex_lock(&p->sh->start_cond_mtx);
	pthread_mutex_unlock(&p->sh->start_cond_mtx);
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal = time_now_ms();
	pthread_mutex_unlock(&p->meal_mtx);
	philosophers_loop(p);
	return (NULL);
}