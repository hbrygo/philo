/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:27 by hugo              #+#    #+#             */
/*   Updated: 2023/10/06 14:10:19 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo_state *p)
{
	if (p->philo->nb_of_meal > 0)
		p->philo->nb_of_meal--;
	else if (p->philo->nb_of_meal == 0)
		return (-1);
	pthread_mutex_lock(&p->philo->fork);
	ft_mut_print(p->philo->id, "has taken a fork", p->philo->printing, p->philo->start_time);
	pthread_mutex_lock(&p->philo->next->fork);
	ft_mut_print(p->philo->id, "has taken a fork", p->philo->printing, p->philo->start_time);
	ft_mut_print(p->philo->id, "is eating", p->philo->printing, p->philo->start_time);
	ft_sleep(p->philo->time_to_eat, p);
	gettimeofday(&p->last_eat, NULL);
	p->state = SLEEP;
	pthread_mutex_unlock(&p->philo->fork);
	pthread_mutex_unlock(&p->philo->next->fork);
	return (0);
}
