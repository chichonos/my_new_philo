/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:58:39 by mea               #+#    #+#             */
/*   Updated: 2022/06/14 10:29:21 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	end_of_the_party(t_table *table)
{
	int		i;

	i = 0;

	ft_sleep(100);
	while (i < table->nb_of_philo - 1)
		pthread_mutex_destroy(table->forks + (i++));
	pthread_mutex_destroy(&table->is_writing);
	pthread_mutex_destroy(&table->is_dying);
	free(table->philo);
	free(table->forks);
}



int main(int argc, char **argv)
{
	t_table table;

	parsing(argc, argv, &table);
	start_the_party(&table);
	end_of_the_party(&table);
	return (0);
}

