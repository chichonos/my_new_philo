/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:11:09 by mea               #+#    #+#             */
/*   Updated: 2022/06/06 14:25:22 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_threads(t_table *table, int i)
{
	pthread_create(&table->philo[i].thread, NULL, dinner_time, &table->philo[i]);
}

/*void	init_forks(t_table *table, int i)
{
		pthread_mutex_init(table->forks + i, NULL);
}
*/

void	init_philo(t_table *table, int i)
{
	t_philo *philo;

	philo = table->philo + i;
	philo->id = i;
	philo->eating = 0;
	philo->sleeping = 0;
	philo->dead = 0;
	philo->nb_of_meal = 0;
	philo->last_meal_time = 0;
	philo->table = table;
	if (i == 0)
		philo->left_fork = table->forks + (table->nb_of_philo - 1);
	else
		philo->left_fork = table->forks + (i - 1);
	philo->right_fork = table->forks + i;
}

void	start_the_party(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_of_philo)
		pthread_mutex_init(table->forks + (i++), NULL);
	i = 0;
	while (i < table->nb_of_philo)
		init_philo(table, i++);
	i = 0;
	while (i < table->nb_of_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, dinner_time, &table->philo[i]);
		i++;
	}
	//philo_check_death(table);
	return ;
}