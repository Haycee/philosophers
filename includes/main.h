/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirardi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:38:39 by agirardi          #+#    #+#             */
/*   Updated: 2022/05/10 16:23:21 by agirardi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_H
# define MAIN_H

# define STOP 0
# define CONTINUE 1

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	struct s_philo  *philo;
	pthread_mutex_t	*check_fork;
	pthread_mutex_t	check_thread_state;
	int				*fork;
	int				thread_state;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	long			starting_time;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_mutex_t	check_last_meal_time;
	pthread_mutex_t	check_meal_counter;
	int				meal_counter;
	int				id;
	long			last_meal_time;
}	t_philo;


/* parsing.c */
int		parse_args(int argc, char **argv);

/* initialization.c */
void	ini_structs(int argc, char **argv, t_data *data, t_philo *philo);
void	ini_mutexes(t_data *data);

/* threads.c */
int launch_threads(t_data *data, pthread_t *thread, t_philo *philo);
int stop_threads(t_data *data, pthread_t *thread, t_philo *philo);

/* routine.c */
void	*routine(void *philosopher);

/* utils.c */
void	free_structs(pthread_t *thread, t_philo *philo);
void	destroy_mutex(t_data *data);
long	get_time(void);

/* lib */
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);

#endif
