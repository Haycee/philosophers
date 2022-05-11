/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/11 09:52:58 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	free_struct(t_data *data)
{
	if (data->check_fork)
		free(data->check_fork);
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
	if (data->thread)
		free(data->thread);
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

void	print_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->check_thread_state);
	if (philo->data->thread_state == RUNNING)
	{
		if (action == TAKEN_FORK)
			printf("[%lu] %d has taken a fork\n",
				get_time() - philo->data->starting_time, philo->id + 1);
		else if (action == EAT)
			printf("[%lu] %d is eating\n",
				get_time() - philo->data->starting_time, philo->id + 1);
		else if (action == SLEEP)
			printf("[%lu] %d is sleeping\n",
				get_time() - philo->data->starting_time, philo->id + 1);
		else if (action == THINK)
			printf("[%lu] %d is thinking\n",
				get_time() - philo->data->starting_time, philo->id + 1);
	}
	if (action == DIED)
		printf("[%lu] %d died\n",
			get_time() - philo->data->starting_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->check_thread_state);
}

void	ft_usleep(int action_duration, t_philo *philo)
{
	long	time_to_stop;

	time_to_stop = get_time() - philo->data->starting_time + action_duration;
	usleep(action_duration * 0.80 * 1000);
	while ((get_time() - philo->data->starting_time) < time_to_stop)
		usleep(500);
}
