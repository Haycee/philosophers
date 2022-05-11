/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/11 05:07:19 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	is_everyone_alive(t_data *data);
static int	is_everyone_full(t_data *data);

void	monitor_threads(t_data *data)
{
	while (1)
	{
		if (!is_everyone_alive(data) || is_everyone_full(data))
		{
			pthread_mutex_lock(&data->check_thread_state);
			data->thread_state = STOPPED;
			pthread_mutex_unlock(&data->check_thread_state);
			return ;
		}
	}
}

static int	is_everyone_alive(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_lock(&data->philo[i].check_last_meal_time);
		if (get_time() - data->philo[i].last_meal_time > data->time_to_die)
		{
			print_action(&data->philo[i], DIED);
			pthread_mutex_unlock(&data->philo[i].check_last_meal_time);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].check_last_meal_time);
	}
	return (1);
}

static int	is_everyone_full(t_data *data)
{
	int	counter;
	int	i;

	if (data->meal_goal < 0)
		return (0);
	counter = 0;
	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_lock(&data->philo[i].check_meal_counter);
		if (data->philo[i].meal_counter >= data->meal_goal)
			counter++;
		pthread_mutex_unlock(&data->philo[i].check_meal_counter);
		if (counter == data->number_of_philos)
			return (1);
	}
	return (0);
}
