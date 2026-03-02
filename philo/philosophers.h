/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:40:28 by abecucci          #+#    #+#             */
/*   Updated: 2026/03/02 19:36:57 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --- LIBRERIE --- */
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
#include "utils.h"

/* --- MACRO --- */
# define SUCCESS 0
# define FAILURE 1
# define MONITOR_SLEEP_TIME_US 1000

/* --- STRUTTURE --- */
typedef enum e_bool
{
	False,
	True
}					t_bool;

typedef struct s_shared
{
	int				n;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				must_eat;
	t_bool			stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	start_cond_mtx;
	pthread_mutex_t	stop_mtx;
	long			start_time;
}					t_shared;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	int				left;
	int				right;
	int				meals;
	int64_t			last_meal;
	pthread_mutex_t	meal_mtx;
	t_shared		*sh;
}					t_philo;

/* --- FUNZIONI --- */
int				init_shared(t_shared *sh, int argc, char **argv);
int				init_philos(t_philo **philos, t_shared *sh);

int				execute_must_eating(t_philo *philos);
int				execute_eating_to_die(t_philo *philos);
void			*routine(void *arg);

void			cleanup(t_shared *sh, t_philo **philos);
int				cleanup_fail(t_shared *sh, t_philo **philos);


#endif //PHILOSOPHERS_H