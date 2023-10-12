/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:10:23 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/12 17:20:06 by hubrygo          ###   ########.fr       */
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
# include <stdatomic.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct s_philosopher
{
	int					id;
	atomic_int			is_fed;
	int					left_fork_id;
	int					right_fork_id;
	time_t				t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					nb_meals;
	atomic_int			all_fed;
	time_t				start_time;
	atomic_int			dead;
	pthread_mutex_t		state_write;
	pthread_mutex_t		*forks;
	t_philosopher		*p;
}						t_rules;

int		ft_init(int argc, char **argv, t_rules *rules);
int		ft_atoi(const char *str);
time_t	get_time(void);
void	ft_sleep(time_t end, t_rules *rules);
void	ft_mut_print(int id, t_rules *rules, char *str);
void	*ft_routine(void *p_void);

#endif