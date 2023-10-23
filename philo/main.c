/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:24 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/23 14:08:49 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_fork(int end, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < end)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	free(rules->forks);
}

void	ft_is_dead(t_rules *rules)
{
	int		i;
	time_t	time;

	while (!rules->all_fed)
	{
		i = -1;
		time = get_time();
		while (++i < rules->nb_philo)
		{
			if ((time - rules->p[i].t_last_meal) > rules->time_to_die)
			{
				ft_mut_print(i, rules, "is dead");
				rules->dead = 1;
				return ;
			}
		}
		i = 0;
		while (rules->nb_meals != -1 && i < rules->nb_philo
			&& rules->nb_meals <= rules->p[i].is_fed)
			i++;
		if (i == rules->nb_philo)
			rules->all_fed = 1;
	}
}

int	ft_exit(int ret, t_rules *rules)
{
	int	i;

	if (ret == 1)
		return (1);
	i = -1;
	while (rules->p && ++i < rules->nb_philo)
		pthread_join(rules->p[i].thread_id, NULL);
	if (ret == 2)
		return (1);
	i = 0;
	while (rules->forks && i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	if (rules->start_time)
		pthread_mutex_destroy(&rules->state_write);
	if (ret == 3)
		return (1);
	free(rules->forks);
	free(rules->p);
	return (0);
}

int	ft_only_one(t_rules *rules)
{
	ft_mut_print(0, rules, "has taken a fork");
	ft_mut_print(rules->time_to_die, rules, "is dead");
	ft_exit(4, rules);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		i;
	int		ret;

	if (argc != 5 && argc != 6)
		return (1);
	ret = ft_init(argc, argv, &rules);
	if (ret != 0)
		return (ft_exit(ret, &rules), 1);
	i = 0;
	rules.start_time = get_time();
	if (rules.nb_philo == 1)
		return (ft_only_one(&rules));
	while (i < rules.nb_philo)
	{
		if (pthread_create(&rules.p[i].thread_id, NULL, 
				ft_routine, (void *)&rules.p[i]))
			return (ft_exit(4, &rules), 1);
		i++;
	}
	ft_sleep(10, &rules);
	ft_is_dead(&rules);
	return (ft_exit(4, &rules));
}
