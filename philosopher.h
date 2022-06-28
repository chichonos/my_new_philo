/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:20:28 by mea               #+#    #+#             */
/*   Updated: 2022/06/28 09:46:40 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eating;
	int				sleeping;
	int				dead;
	int				nb_of_meal;
	int				last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meal_min;
	int				stop;
	int				death;
	t_philo			*philo;
	size_t			start_time;
	pthread_mutex_t	is_writing;
	pthread_mutex_t	is_dying;
	pthread_mutex_t	*forks;
}				t_table;

/* --------------- FUNCTIONS ---------------- */

//time.c

int			actual_time(void);
void		ft_sleep(long int time);
int			philo_sleep(t_philo *philo, long int time_in_ms);

//utils.c
int			ft_atoi(const char *str);
void		print_action(int time, t_philo *philo, char *msg);

//init.c
void		init_threads(t_table *table, int i);
void		init_forks(t_table *table, int i);
void		init_philo(t_table *table, int i);
int			death_checker(t_philo *philo);
int			meal_checker(t_philo *philo);

//dinner.c
void		*dinner_time(void *data);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//parsing.c

int			parsing(int argc, char **argv, t_table *table);

//main.c
void		start_the_party(t_table *table);
void		end_of_the_party(t_table *table);

#endif
