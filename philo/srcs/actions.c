/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/19 22:09:10 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	take_forks(t_philo *philo, t_data *data);
static void	drop_forks(t_philo *philo, t_data *data);

void	ft_eat(t_philo *philo)
{
	take_forks(philo, philo->data);
	if (!check_state(philo))
	{
		drop_forks(philo, philo->data);
		return ;
	}
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->check_last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->check_last_meal_time);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->check_meal_counter);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->check_meal_counter);
	drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep, philo);
}

static void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->id == 0)
	{
		pthread_mutex_lock(&data->check_fork[data->number_of_philos - 1]);
		data->fork[data->number_of_philos - 1] = TAKEN;
	}
	else
	{
		pthread_mutex_lock(&data->check_fork[philo->id - 1]);
		data->fork[philo->id - 1] = TAKEN;
	}
	pthread_mutex_lock(&data->check_fork[philo->id]);
	data->fork[philo->id] = TAKEN;
	print_action(philo, TAKE_FORK);
}

static void	drop_forks(t_philo *philo, t_data *data)
{
	if (philo->id == 0)
	{
		data->fork[data->number_of_philos - 1] = FREE;
		pthread_mutex_unlock(&data->check_fork[data->number_of_philos - 1]);
	}
	else
	{
		data->fork[philo->id - 1] = FREE;
		pthread_mutex_unlock(&data->check_fork[philo->id - 1]);
	}
	data->fork[philo->id] = FREE;
	pthread_mutex_unlock(&data->check_fork[philo->id]);
}
