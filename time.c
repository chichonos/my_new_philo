/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:20:04 by mea               #+#    #+#             */
/*   Updated: 2022/06/06 15:22:10 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

size_t	convert_time_in_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time_ms_now(void)
{
	return (convert_time_in_ms(get_time()));
}

size_t	convert_time_in_ms_from_start(t_table *table)
{
	return (get_time_ms_now() - table->start_time);
}

void	ft_sleep(size_t usec)
{
	size_t	current;

	current = get_time_ms_now();
	while (usec > get_time_ms_now() - current)
		usleep(usec * 1000);
}