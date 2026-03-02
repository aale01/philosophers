/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:25:49 by abecucci          #+#    #+#             */
/*   Updated: 2026/03/02 19:51:49 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	fork_taken(t_philo *p, int fork)
{
	pthread_mutex_lock(&p->sh->forks[fork]);
	if (should_stop(p->sh))
	{
		// printf("check: philo %d with fork %d\n", p->id, fork);
		pthread_mutex_unlock(&p->sh->forks[fork]);
		return (False);
	}
	print_state(p, "has taken a fork");
	return (True);
}

static t_bool	take_forks_no_deadlock(t_philo *p, int *first, int *second)
{
	int a;
	int b;

	a = p->left;
	b = p->right;
	if (a < b)
	{
		*first = a;
		*second = b;
	}
	else
	{
		*first = b;
		*second = a;
	}
	if (!fork_taken(p, *first))
		return (False);
	if (!fork_taken(p, *second))
	{
		pthread_mutex_unlock(&p->sh->forks[*first]);
		return (False);
	}
	return (True);
}

static void	philosophers_loop(t_philo *p)
{
	int	first;
	int	second;

	while (!should_stop(p->sh))
	{
		if (take_forks_no_deadlock(p, &first, &second) == False)
			break ;
		pthread_mutex_lock(&p->last_meal_mtx);
		p->last_meal = time_now_ms();
		pthread_mutex_unlock(&p->last_meal_mtx);
		print_state(p, "is eating");
		usleep(p->sh->t_eat * 1000);
		p->meals++;
		pthread_mutex_unlock(&p->sh->forks[second]);
		pthread_mutex_unlock(&p->sh->forks[first]);
		if (should_stop(p->sh))
			break ;
		print_state(p, "is sleeping");
		usleep(p->sh->t_sleep * 1000);
		if (should_stop(p->sh))
			break ;
		print_state(p, "is thinking");
	}
}

void	*routine(void *arg)
{
	t_philo *p;

	p = (t_philo *) arg;
	pthread_mutex_lock(&p->sh->start_cond_mtx);
	pthread_mutex_unlock(&p->sh->start_cond_mtx);
	philosophers_loop(p);
	return (NULL);
}