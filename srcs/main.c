/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/11 02:42:34 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
	print erreurs ?
	check free_structs -> *check_fork & *fork
	supprimer ft_think si juste une ligne
	tableau de fork ne sert a rien ?

	philo[i].last_meal_time = get_time(); delay ?
*/

int	main(int argc, char **argv)
{
	t_data		data;
	int			status;

	if (!parse_args(argc, argv))
		return (1);
	if (!ini_structs(argc, argv, &data))
	{
		free_struct(&data);
		return (1);
	}
	status = launch_threads(&data, data.thread, data.philo);
	destroy_mutex(&data);
	free_struct(&data);
	return (status);
}
