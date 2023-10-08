/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:26:28 by hugo              #+#    #+#             */
/*   Updated: 2023/10/06 13:48:11 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo_state *p)
{
	if (ft_is_dead(p->philo->mut_dead, p->philo->death))
		return (-1);
	ft_mut_print(p->philo->id, "is sleeping", p->philo->printing, p->philo->start_time);
	ft_sleep(p->philo->time_to_sleep, p);
	p->state = THINK;
	return (0);
}
