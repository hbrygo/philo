/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:01:00 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/25 18:17:29 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_allocation(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philos)
		return (1);
	data->thread_id = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->thread_id)
		return (1);
	return (0);
}

void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philos[i].data = data;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].is_eating = 0;
		data->philos[i].id = i + 1;
		data->philos[i].number_of_meal = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

void	ft_init_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->nb_of_philo - 1];
	i = 0;
	while (++i < data->nb_of_philo)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
	}
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->nb_of_meals = 0;
	if (argc == 6)
	{
		data->nb_of_meals = ft_atoi(argv[5]);
		if (data->nb_of_meals <= 0)
			return (printf("Error: information\n"));
	}
	if (data->death_time <= 0 || data->eat_time <= 0
		|| data->sleep_time <= 0 || data->nb_of_philo <= 0)
		return (printf("Error: information\n"));
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	return (0);
}

int	ft_init(t_data *data, int argc, char **argv)
{
	if (ft_init_data(data, argc, argv) != 0)
		return (1);
	if (ft_init_allocation(data) != 0)
		return (1);
	ft_init_fork(data);
	ft_init_philo(data);
	return (0);
}
