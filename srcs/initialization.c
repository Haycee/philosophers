/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 16:38:41 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ini_structs(int argc, char **argv, t_data *data, t_philo *philo)
{
	int	i;

	data->philo = philo;
	data->fork = calloc(ft_atoi(argv[1]), sizeof(int));
	data->thread_state = CONTINUE;
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meal_goal = ft_atoi(argv[5]);
	else
		data->meal_goal = -1;
	i = -1;
	while (++i < data->number_of_philos)
	{
		philo[i].data = data;
		philo[i].last_meal_time = get_time();
		philo[i].meal_counter = 0;
		philo[i].id = i;
	}
}

void	ini_mutexes(t_data *data)
{
	int i;

	pthread_mutex_init(&data->check_thread_state, NULL);
	data->check_fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_init(&data->check_fork[i], NULL);
		pthread_mutex_init(&data->philo[i].check_last_meal_time, NULL);
		pthread_mutex_init(&data->philo[i].check_meal_counter, NULL);
	}
}
