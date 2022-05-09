/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:38:39 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/09 17:12:41 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_H
# define MAIN_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* main.c */

/* parsing.c */

int		parse_args(int argc, char **argv);

/* lib */

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);

#endif
