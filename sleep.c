/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:25:14 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/06 11:18:13 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
{
	static struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec) / 1000);
}

int	ft_sleep(int end, t_philo_state *p)
{
	long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(p->philo->mut_dead);
		if (*p->philo->death == 1)
		{
			pthread_mutex_unlock(p->philo->mut_dead);
			return (1);
		}
		pthread_mutex_unlock(p->philo->mut_dead);
		if (get_time() - start >= end)
			break;
		usleep(50);
	}
	return (0);
}
