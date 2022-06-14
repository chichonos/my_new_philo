/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:11:09 by mea               #+#    #+#             */
/*   Updated: 2022/06/14 15:02:52 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_threads(t_table *table, int i)
{
	pthread_create(&table->philo[i].thread, NULL, dinner_time, \
	&table->philo[i]);
}

void	init_philo(t_table *table, int i)
{
	table->philo[i].id = i + 1;
	table->philo[i].eating = 0;
	table->philo[i].sleeping = 0;
	table->philo[i].dead = 0;
	table->philo[i].nb_of_meal = 0;
	table->philo[i].last_meal_time = 0;
	table->philo[i].table = table;
	if (i == 0)
		table->philo[i].left_fork = table->forks + (table->nb_of_philo - 1);
	else
		table->philo[i].left_fork = table->forks + (i - 1);
	table->philo[i].right_fork = table->forks + i;
}

void	start_the_party(t_table *table)
{
	int		i;

	pthread_mutex_init(&table->is_writing, NULL);
	pthread_mutex_init(&table->is_dying, NULL);
	i = 0;
	while (i < table->nb_of_philo)
		pthread_mutex_init(table->forks + (i++), NULL);
	i = 0;
	while (i < table->nb_of_philo)
		init_philo(table, i++);
	if (table->nb_of_philo == 1)
	{
		print_action(actual_time(), &table->philo[0], "is dead\n");
		return ;
	}
	i = -1;
	while (++i < table->nb_of_philo)
		pthread_create(&table->philo[i].thread, NULL, dinner_time, \
		&table->philo[i]);
	i = -1;
	while (++i < table->nb_of_philo)
		pthread_join(table->philo[i].thread, NULL);
	return ;
}
