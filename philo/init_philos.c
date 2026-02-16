#include "philosophers.h"

int	init_philos(t_philo **philos, t_shared *sh)
{
	int	i;

	*philos = (t_philo *)malloc(sh->n * sizeof(t_philo));
	if (!*philos)
		return (FAILURE);
	i = 0;
	while (i < sh->n)
	{
		(*philos)[i].id = i;
		(*philos)[i].left = (i + sh->n - 1) % sh->n;
		(*philos)[i].right = (i + 1) % sh->n;
		(*philos)[i].sh = sh;
		i++;
	}
	return (SUCCESS);
}
