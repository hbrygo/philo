/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:57:13 by hugo              #+#    #+#             */
/*   Updated: 2023/10/07 14:08:24 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(pthread_mutex_t *mut_dead, int	*death)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(mut_dead) == -1)
		return (-1);
	if (*death == 1)
		ret = 1;
	pthread_mutex_unlock(mut_dead);
	return (ret);
}

int	ft_death(t_philo_state *p)
{
	gettimeofday(&p->end, NULL);
	if (ft_calcul(p->last_eat, p->end) < p->philo->time_to_die)
	{
		if (ft_is_dead(p->philo->mut_dead, p->philo->death))
			return (-1);
		ft_mut_print(p->philo->id, "died", p->philo->printing, p->philo->start_time);
		*p->philo->death = 1;
		return (-1);
	}
	return (0);
}
