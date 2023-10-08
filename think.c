/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:26:07 by hugo              #+#    #+#             */
/*   Updated: 2023/10/06 13:42:48 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_think(t_philo_state *p)
{
	if (ft_is_dead(p->philo->mut_dead, p->philo->death) || !p->philo->nb_of_meal)
		return (-1);
	ft_mut_print(p->philo->id, "is thinking", p->philo->printing, p->philo->start_time);
	return (0);
}
