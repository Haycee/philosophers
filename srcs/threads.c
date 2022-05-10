/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 17:38:11 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int stop_threads(t_data *data, pthread_t *thread);

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	// cas particulié si 1 philo
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_eat(philo);
	}
	return ((void *)1);
}

int launch_threads(t_data *data, pthread_t *thread, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		usleep(1);
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
			return (0);
	}
	// check ici ?
	if (!stop_threads(data, thread))
		return (0);
	return (1);
}

static int stop_threads(t_data *data, pthread_t *thread)
{
	int i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (0);
	}
	return (1);
}