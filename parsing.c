/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:11:59 by mea               #+#    #+#             */
/*   Updated: 2022/06/06 14:18:21 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_table(t_table *table)
{
	if (table->nb_of_philo < 2 || \
	table->nb_of_philo > 7)
		return (printf("Wrong number of philosophers\n"));
	if (table->time_to_die < 0 || table->time_to_die > 100)
		return (printf("Wrong time to die\n"));
	if (table->time_to_eat < 0 || table->time_to_eat > 100)
		return (printf("Wrong time to eat\n"));
	if (table->time_to_sleep < 0 || table->time_to_sleep > 100)
		return (printf("Wrong time to sleep\n"));
	return (0);
}

void parsing(int argc, char **argv, t_table *table)
{
	
	if (argc < 5)
		return ;
	table->nb_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nb_of_meal = ft_atoi(argv[5]);
	if(check_table(table))
		return ;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->nb_of_philo);
	if (table->philo == NULL)
		return ;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_of_philo);
	if (table->forks == NULL)
		return ;
	pthread_mutex_init(&table->is_writing, NULL);
}

