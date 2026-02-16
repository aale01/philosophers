/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:23:28 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/16 23:40:43 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_shared	shared;

	if (init_shared(&shared, argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	if (init_philos(&philos, &shared) != SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
void *thread(void *arg) {
	char *ret;
	printf("thread() entered with argument '%s'\n", (char *)arg);
	if ((ret = (char*) malloc(20)) == NULL) {
		perror("malloc() error");
		exit(2);
	}
	strcpy(ret, "This is a test");
	pthread_exit(ret);
}

int main() {
	pthread_t thid;
	void *ret;

	if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
		perror("pthread_create() error");
		exit(1);
	}

	if (pthread_join(thid, &ret) != 0) {
		perror("pthread_create() error");
		exit(3);
	}

	printf("thread exited with '%s'\n", (char *)ret);
}
*/