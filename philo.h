/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:30:07 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/06 14:08:41 by hugo             ###   ########.fr       */
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
# define DEATH 4

typedef struct s_philo
{
	int						nb_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_of_meal;
	int						id;
	int						*death;
	long					start_time;
	struct s_philo			*next;
	pthread_mutex_t			fork;
	pthread_mutex_t			*printing;
	pthread_mutex_t			*mut_dead;
}					t_philo;

typedef struct s_philo_param
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death;
	int				nb_to_eat;
	long			start;
	t_philo			*philos;
	pthread_t		*thread_p;
	pthread_mutex_t	printing;
	pthread_mutex_t	mut_dead_param;
}					t_philo_param;

typedef struct s_philo_state
{
	int				state;
	int				thinking;
	int				thinking_ret;
	struct timeval	last_eat;
	struct timeval	end;
	t_philo			*philo;
	t_philo			*right_philo;
	t_philo_param	p_param;
}					t_philo_state;

int				ft_atoi(const char *str);
int				ft_init(t_philo_param *philo, int argc, char **argv);
int				ft_sleep(int end, t_philo_state *p);
long			get_time();
t_philo			*ft_create_philo(t_philo_param *philo_param, int i);
int				ft_mut_print(int id, char *str, pthread_mutex_t *print, long start);
int				ft_eat(t_philo_state *p);
int				ft_is_dead(pthread_mutex_t *mut_dead, int	*status);
int				ft_philo_releaser(pthread_mutex_t *fork, int *state_of_fork,
int 			*total_fork);
int				philo_sleep(t_philo_state *p);
int				ft_think(t_philo_state *p);
int				ft_death(t_philo_state *p);
unsigned long	to_u_long(struct timeval tv);
int				ft_calcul(struct timeval start, struct timeval end);

#endif