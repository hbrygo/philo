/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:03:54 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/12 15:06:42 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != 0)
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				printf("Only need positiv int\n");
				return (1);
			}
		}
	}
	return (0);
}

int	ft_verif_input(t_rules *rules, int argc)
{
	if (argc == 6 && rules->nb_meals <= 0)
		return (1);
	if (rules->nb_philo < 1 || rules->time_to_die < 0)
		return (1);
	if (rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (1);
	return (0);
}

int	ft_init_mutex(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
		{
			free(rules->forks);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&(rules->state_write), NULL))
	{
		free(rules->forks);
		return (1);
	}
	return (0);
}

void	ft_init_philo(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	rules->p = malloc(sizeof(t_philosopher) * rules->nb_philo);
	if (!rules->p)
		return ;
	while (--i >= 0)
	{
		rules->p[i].id = i;
		rules->p[i].is_fed = 0;
		rules->p[i].left_fork_id = i;
		rules->p[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->p[i].rules = rules;
	}
}

int	ft_init(int argc, char **argv, t_rules *rules)
{
	if (ft_check_arg(argc, argv) == -1)
		return (1);
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->nb_meals = -1;
	if (argc == 6)
		rules->nb_meals = ft_atoi(argv[5]);
	if (ft_verif_input(rules, argc) == 1)
		return (1);
	if (ft_init_mutex(rules) == 1)
		return (1);
	rules->all_fed = 0;
	rules->dead = 0;
	ft_init_philo(rules);
	if (!rules->p)
		return (1);
	return (0);
}
