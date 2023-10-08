/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:11:33 by hugo              #+#    #+#             */
/*   Updated: 2023/10/06 13:13:19 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_calcul(struct timeval start, struct timeval end)
{
	return (to_u_long(end) - to_u_long(start));
}
unsigned long	to_u_long(struct timeval tv)
{
	return ((tv.tv_sec * 1000 + tv.tv_usec) / 1000);
}

int	ft_mut_print(int id, char *str, pthread_mutex_t *print, long start)
{
	if (pthread_mutex_lock(print) == -1)
		return (-1);
	printf("%ld %d %s\n", get_time() - start, id, str);
	if (pthread_mutex_unlock(print) == -1)
		return (-1);
	return (0);
}

int	ft_philo_releaser(pthread_mutex_t *fork, int *state_of_fork,
		int *total_fork)
{
	int	ret;

	ret = -1;
	if (pthread_mutex_lock(fork) == -1)
		return (ret);
	if (*state_of_fork == 0)
	{
		*state_of_fork = 1;
		(*total_fork)--;
		ret = 0;
	}
	if (pthread_mutex_unlock(fork) == -1)
		return (-1);
	return (ret);
}
