/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:30:07 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/01 16:59:11 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define EAT 1
# define SLEEP 2
# define THINK 3

typedef struct s_philo
{
	int				id;
	int				number_of_meal;
	int				status;
	int				is_eating;
	int				time_to_die;
	int				fork_available;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}				t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				nb_of_meals;
	int				dead;
	int				finished;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				start_time;
	t_philo			*philos;
	pthread_t		*thread_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	write;
}				t_data;

int		ft_atoi(const char *str);
int		ft_init(t_data *data, int argc, char **argv);
int		ft_sleep(long end, t_data *data);
long	get_time();

#endif