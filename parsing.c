/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:11:59 by mea               #+#    #+#             */
/*   Updated: 2022/06/14 15:00:21 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_table(t_table *table)
{
	if (table->nb_of_philo < 0 || table->nb_of_philo > 200)
	{
		printf("Wrong number of philosophers\n");
		return (1);
	}
	return (0);
}

int	parsing(int argc, char **argv, t_table *table)
{
	if (argc < 5)
		return (1);
	table->nb_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nb_of_meal_min = ft_atoi(argv[5]);
	if (check_table(table))
		return (1);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->nb_of_philo);
	if (table->philo == NULL)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_of_philo);
	if (table->forks == NULL)
		return (1);
	table->death = 0;
	table->stop = 0;
	table->start_time = actual_time();
	return (0);
}
