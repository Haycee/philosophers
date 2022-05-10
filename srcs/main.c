/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 15:25:25 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
	int id dans struct philo
*/

int	main(int argc, char **argv)
{
	pthread_t	*thread;
	t_philo		*philo;
	t_data		data;

	if (!parse_args(argc, argv))
		return (1);
	thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!thread || !philo)
	{
		free_structs(thread, philo);
		return (1);
	}
	ini_structs(argc, argv, &data, philo);
	ini_mutexes(&data);
	return (0);
}
