/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:20:28 by mea               #+#    #+#             */
/*   Updated: 2022/06/03 15:16:27 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_table;

typedef struct s_philo
{
	int				id;
	int				eating;
	int 			sleeping;
	int				dead;
	int				nb_of_meal;
	int 			last_meal_time;
	pthread_t 		thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_table 	*table;
}				t_philo;

typedef struct s_table
{
	int	nb_of_philos;
   	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	t_philo *philo;
	pthread_t *forks;
}				t_table;

t_table parsing(int argc, char **argv);
void	start_the_party(t_table table);
void	end_of_the_party(t_table table);

#endif
