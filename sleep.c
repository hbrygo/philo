/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:25:14 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/01 13:36:48 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
{
	static struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_sleep(long end, t_data *data)
{
	long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->m_dead);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->m_dead);
			return (1);
		}
		pthread_mutex_unlock(&data->m_dead);
		if (get_time() - start >= end)
			break;
		usleep(100);
	}
	return (0);
}
