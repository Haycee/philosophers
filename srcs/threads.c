/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 16:51:13 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int stop_threads(t_data *data, pthread_t *thread);

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