/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:01:00 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/06 14:11:18 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

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
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf("Only need int\n");
				return (1);
			}
		}
	}
	return (0);
}

int	ft_init(t_philo_param *philo, int argc, char **argv)
{
	if (ft_check_arg(argc, argv) == -1)
		return (-1);
	philo->nb_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->nb_to_eat = -1;
	philo->philos = NULL;
	philo->death = 0;
	if (argc == 6)
		philo->nb_to_eat = ft_atoi(argv[5]);
	if (philo->nb_philo < 1)
		return (-1);
	philo->thread_p = (pthread_t *)malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!philo->thread_p)
		return (-1);
	if (pthread_mutex_init(&philo->printing, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&philo->mut_dead_param, NULL) == -1)
	{
		pthread_mutex_destroy(&philo->printing);
		return (-1);
	}
	return (0);
}

t_philo	*ft_create_philo(t_philo_param *philo_param, int i)
{
	t_philo	*ptr;

	ptr = (t_philo *)malloc(sizeof(t_philo) * (philo_param->nb_philo + 1));
	if (!ptr)
		return (NULL);
	while (i < philo_param->nb_philo)
	{
		if (pthread_mutex_init(&ptr[i].fork, NULL))
			return (NULL);
		ptr[i].id = i + 1;
		ptr[i].nb_philo = philo_param->nb_philo;
		ptr[i].time_to_die = philo_param->time_to_die;
		ptr[i].time_to_eat = philo_param->time_to_eat;
		ptr[i].time_to_sleep = philo_param->time_to_sleep;
		ptr[i].nb_of_meal = philo_param->nb_to_eat;
		ptr[i].printing = &philo_param->printing;
		ptr[i].mut_dead = &philo_param->mut_dead_param;
		ptr[i].death = &philo_param->death;
		ptr[i].start_time = philo_param->start;
		i++;
	}
	ptr[i].id = 0;
	return (ptr);
}
