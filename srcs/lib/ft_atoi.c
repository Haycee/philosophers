/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:21:32 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/09 17:11:34 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	if (result > INT_MAX)
		return (-1);
	return (result);
}
