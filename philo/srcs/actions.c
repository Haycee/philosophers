/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/11 09:50:25 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	take_forks(t_philo *philo);
static void	drop_forks(t_philo *philo);

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	if (!check_state(philo))
	{
		drop_forks(philo);
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

static void	take_forks(t_philo *philo)
{
	if (philo->id == 0)
	{
		pthread_mutex_lock(&philo->data->check_fork[philo->data->number_of_philos - 1]);
		philo->data->fork[philo->data->number_of_philos - 1] = TAKEN;
	}
	else
	{
		pthread_mutex_lock(&philo->data->check_fork[philo->id - 1]);
		philo->data->fork[philo->id - 1] = TAKEN;
	}
	pthread_mutex_lock(&philo->data->check_fork[philo->id]);
	philo->data->fork[philo->id] = TAKEN;
	print_action(philo, TAKEN_FORK);
}

static void	drop_forks(t_philo *philo)
{
	if (philo->id == 0)
	{
		philo->data->fork[philo->data->number_of_philos - 1] = FREE;
		pthread_mutex_unlock(&philo->data->check_fork[philo->data->number_of_philos - 1]);
	}
	else
	{
		philo->data->fork[philo->id - 1] = FREE;
		pthread_mutex_unlock(&philo->data->check_fork[philo->id - 1]);
	}
	philo->data->fork[philo->id] = FREE;
	pthread_mutex_unlock(&philo->data->check_fork[philo->id]);
}