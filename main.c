/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:24 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/12 17:12:25 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				ft_sleep(100, rules);
				return ;
			}
			ft_sleep(100, rules);
		}
		i = 0;
		while (rules->nb_meals != -1 && i < rules->nb_philo
			&& rules->nb_meals <= rules->p[i].is_fed)
			i++;
		if (i == rules->nb_philo)
			rules->all_fed = 1;
	}
}

void	ft_exit(t_rules *rules)
{
	int	i;

	i = -1;
	while (rules->p && ++i < rules->nb_philo)
		pthread_join(rules->p[i].thread_id, NULL);
	if (rules->all_fed)
	{
		i = -1;
		while (++i < rules->nb_philo)
			printf("\033[35;01mphilo %d has eaten %d times\n", \
				i + 1, rules->p[i].is_fed + 1);
	}
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->state_write);
	free(rules->forks);
	free(rules->p);
}

int	ft_only_one(t_rules *rules)
{
	ft_mut_print(0, rules, "has taken a fork");
	ft_mut_print(rules->time_to_die, rules, "is dead");
	ft_exit(rules);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	int				i;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_init(argc, argv, &rules) == 1)
		return (ft_exit(&rules), 1);
	i = 0;
	rules.start_time = get_time();
	if (rules.nb_philo == 1)
		return (ft_only_one(&rules));
	while (i < rules.nb_philo)
	{
		if (pthread_create(&rules.p[i].thread_id, NULL, 
				ft_routine, (void *)&rules.p[i]))
			return (ft_exit(&rules), 1);
		i++;
	}
	ft_is_dead(&rules);
	ft_exit(&rules);
	return (0);
}
