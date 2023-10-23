/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:46:05 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/23 14:08:22 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philosopher *p, int id)
{
	t_rules	*rules;

	rules = p->rules;
	pthread_mutex_lock(&(rules->forks[p->left_fork_id]));
	ft_mut_print(p->id, rules, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[p->right_fork_id]));
	ft_mut_print(p->id, rules, "has taken a fork");
	ft_mut_print(p->id, rules, "is eating");
	rules->p[id].t_last_meal = get_time();
	(p->is_fed)++;
	ft_sleep(rules->time_to_eat, rules);
	pthread_mutex_unlock(&(rules->forks[p->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[p->right_fork_id]));
}

void	*ft_routine(void *p_void)
{
	t_rules			*rules;
	t_philosopher	*p;

	p = (t_philosopher *)p_void;
	rules = p->rules;
	p->t_last_meal = rules->start_time;
	if (p->id % 2)
		ft_sleep(10, rules);
	while (rules->dead != 1)
	{
		ft_eat(p, p->id);
		if (rules->all_fed)
			break ;
		ft_mut_print(p->id, rules, "is sleeping");
		ft_sleep(rules->time_to_sleep, rules);
		ft_mut_print(p->id, rules, "is thinking");
	}
	return (NULL);
}
