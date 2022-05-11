/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:32:16 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/11 09:49:40 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
	print erreurs
*/

int	main(int argc, char **argv)
{
	t_data		data;

	if (!parse_args(argc, argv))
		return (0);
	if (!ini_structs(argc, argv, &data))
	{
		free_struct(&data);
		return (0);
	}
	launch_threads(&data, data.thread, data.philo);
	destroy_mutex(&data);
	free_struct(&data);
	return (0);
}
