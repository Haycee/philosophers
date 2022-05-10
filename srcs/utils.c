/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 15:36:51 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_structs(pthread_t *thread, t_philo *philo)
{
		if (thread)
			free(thread);
		if (philo)
			free(philo);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->check_thread_state);
	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->check_fork[i]);
		pthread_mutex_destroy(&data->philo[i].check_last_meal_time);
		pthread_mutex_destroy(&data->philo[i].check_meal_counter);
	}
}