/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 20:18:00 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	take_forks(t_philo *philo);
static void	drop_forks(t_philo *philo);
static int	should_continue(t_philo *philo); // debug

void	ft_eat(t_philo *philo)
{
	take_forks(philo);

	if (!should_continue(philo)) // debug 
		return ;

	print_action(philo, EAT);

	pthread_mutex_lock(&philo->check_last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->check_last_meal_time);

	usleep(philo->data->time_to_eat * 1000);

	pthread_mutex_lock(&philo->check_meal_counter);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->check_meal_counter);

	drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	print_action(philo, THINK);
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
		pthread_mutex_unlock(&philo->data->check_fork[philo->data->number_of_philos - 1]);
		philo->data->fork[philo->data->number_of_philos - 1] = FREE;
	}
	else
	{
		pthread_mutex_unlock(&philo->data->check_fork[philo->id - 1]);
		philo->data->fork[philo->id - 1] = FREE;
	}
	pthread_mutex_unlock(&philo->data->check_fork[philo->id]);
	philo->data->fork[philo->id] = FREE;
}



/* debug */

static int	should_continue(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->data->check_thread_state);
	state = philo->data->thread_state;
	pthread_mutex_unlock(&philo->data->check_thread_state);
	return (state);
}