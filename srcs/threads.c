/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 18:24:58 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int stop_threads(t_data *data, pthread_t *thread);
static int	should_continue(t_philo *philo);

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	// cas particulié si 1 philo
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!should_continue(philo))
			break;
		ft_eat(philo);
		if (!should_continue(philo))
			break;
		ft_sleep(philo);
		if (!should_continue(philo))
			break;
		ft_think(philo);
	}
	return ((void *)1);
}

int launch_threads(t_data *data, pthread_t *thread, t_philo *philo)
{
	int	i;

	data->starting_time = get_time();
	i = -1;
	while (++i < data->number_of_philos)
	{
		usleep(1);
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
			return (0);
	}
	// check death
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

static int	should_continue(t_philo *philo)
{
	int	state;
	pthread_mutex_lock(&philo->data->check_thread_state);
	state = philo->data->thread_state;
	pthread_mutex_unlock(&philo->data->check_thread_state);
	return (state);
}