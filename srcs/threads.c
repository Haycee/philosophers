/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 23:46:00 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	monitor_threads(t_data *data);
static int stop_threads(t_data *data, pthread_t *thread);
static int	check_state(t_philo *philo);

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	// cas particulier si 1 philo
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_state(philo) == STOPPED)
			break;
		ft_eat(philo);
		if (check_state(philo) == STOPPED)
			break;
		ft_sleep(philo);
		if (check_state(philo) == STOPPED)
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
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
			return (0);
	}
	monitor_threads(data);
	if (!stop_threads(data, thread))
		return (0);
	return (1);
}

static void	monitor_threads(t_data *data)
{
	int	stop;
	int	i;

	stop = 0;
	while (1)
	{
		i = -1;
		while (++i < data->number_of_philos)
		{
			pthread_mutex_lock(&data->philo[i].check_last_meal_time);
			if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->check_thread_state);
				data->thread_state = STOPPED;
				stop = 1;
				pthread_mutex_unlock(&data->check_thread_state);
				print_action(&data->philo[i], DIED);
			}
			pthread_mutex_unlock(&data->philo[i].check_last_meal_time);
			if (stop == 1)
			return ;
		}
	}
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

static int	check_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->data->check_thread_state);
	state = philo->data->thread_state;
	pthread_mutex_unlock(&philo->data->check_thread_state);
	return (state);
}