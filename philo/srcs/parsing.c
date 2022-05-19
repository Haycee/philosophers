/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:44:52 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/19 23:02:22 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static int	is_number(char *arg);
static int	check_limits(char *arg);

int	parse_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Number of arguments is invalid.\n");
		return (0);
	}
	i = 1;
	while (i != argc)
	{
		if (!is_number(argv[i]) || !check_limits(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			printf("Error: Arguments should only consist of integers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_limits(char *arg)
{
	if (ft_atoi(arg) == -1)
	{
		printf("Error: Arguments should be an int.\n");
		return (0);
	}
	return (1);
}
