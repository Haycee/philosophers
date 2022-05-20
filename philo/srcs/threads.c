/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/20 09:49:21 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	stop_threads(t_data *data, pthread_t *thread);

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->data->number_of_philos == 1)
		usleep(philo->data->time_to_die * 1000);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		print_action(philo, THINK);
		if (check_state(philo) == STOPPED)
			break ;
		ft_eat(philo);
		if (check_state(philo) == STOPPED)
			break ;
		ft_sleep(philo);
		if (check_state(philo) == STOPPED)
			break ;
	}
	return ((void *)1);
}

int	launch_threads(t_data *data, pthread_t *thread, t_philo *philo)
{
	int	i;

	data->starting_time = get_time();
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
		{
			printf("Error: Creation of a thread failed.\n");
			return (0);
		}
	}
	monitor_threads(data);
	if (!stop_threads(data, thread))
		return (0);
	return (1);
}

static int	stop_threads(t_data *data, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (0);
	}
	return (1);
}

int	check_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->data->check_thread_state);
	state = philo->data->thread_state;
	pthread_mutex_unlock(&philo->data->check_thread_state);
	return (state);
}
