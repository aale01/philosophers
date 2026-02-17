/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:06:57 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/16 23:12:03 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_positive_int(const char *s, long *out)
{
	long	acc;
	int		i;

	if (!s || !*s || !out)
		return (0);
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+')
		i++;
	if (s[i] == '-' || s[i] == '\0')
		return (0);
	acc = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		acc = acc * 10 + (s[i] - '0');
		if (acc > INT_MAX)
			return (0);
		i++;
	}
	*out = (int)acc;
	return (1);
}

static int	parse_args(t_shared *sh, int argc, char **argv)
{
	if (!sh || !argv || argc < 5 || argc > 6)
		return (FAILURE);
	if (!parse_positive_int(argv[1], (long *)&sh->n)
		|| !parse_positive_int(argv[2], &sh->t_die)
		|| !parse_positive_int(argv[3], &sh->t_eat)
		|| !parse_positive_int(argv[4], &sh->t_sleep))
		return (FAILURE);
	if (sh->n < 1
		|| sh->t_die < 1
		|| sh->t_eat < 1
		|| sh->t_sleep < 1)
		return (FAILURE);
	if (argc == 6)
	{
		if (!parse_positive_int(argv[5], (long *)&sh->must_eat)
			|| sh->must_eat < 1)
		return (FAILURE);
	}
	else
		sh->must_eat = -1;
	return (SUCCESS);
}

int	init_shared(t_shared *sh, int argc, char **argv)
{
	int i;

	if (!sh)
		return (FAILURE);
	if (parse_args(sh, argc, argv) != SUCCESS)
		return (FAILURE);
	sh->start = 0;
	sh->forks = (pthread_mutex_t *)malloc(sh->n * sizeof(pthread_mutex_t));
	i = 0;
	while (i < sh->n)
		pthread_mutex_init(&sh->forks[i++], NULL);
	pthread_mutex_init(&sh->print_mtx, NULL);
	pthread_mutex_init(&sh->state_mtx, NULL);
	return (SUCCESS);
}