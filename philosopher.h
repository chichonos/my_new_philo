/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:20:28 by mea               #+#    #+#             */
/*   Updated: 2022/06/08 13:59:05 by mea              ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				eating;
	int 			sleeping;
	int				dead;
	int				nb_of_meal;
	long int 		last_meal_time;
	pthread_t 		thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_table 	*table;
}				t_philo;

typedef struct s_table
{
	int				nb_of_philo;
   	long int		time_to_die;
	long int		time_to_eat;
	long int 		time_to_sleep;
	int				nb_of_meal_min;
	int				death;
	t_philo 		*philo;
	size_t			start_time;
	pthread_mutex_t is_writing;
	pthread_mutex_t is_dying;
	pthread_mutex_t *forks;
}				t_table;


/* --------------- FUNCTIONS ---------------- */

//time.c

long int	actual_time(void);
long int	convert_time_in_ms_from_start(t_table *table);
void		ft_sleep(long int time);

//utils.c
int		ft_atoi(const char *str);
void	print_action(long int time, t_philo *philo, char *msg);

//init.c
void	init_threads(t_table *table, int i);
void	init_forks(t_table *table, int i);
void	init_philo(t_table *table, int i);
void	philo_check_death(t_table *table);
int		philo_check_eat(t_table *table);

//dinner.c

void	ft_sleep(long int time);
void	*dinner_time(void *data);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//parsing.c
void parsing(int argc, char **argv, t_table *table);

//main.c
void	start_the_party(t_table *table);
void	end_of_the_party(t_table *table);

#endif
