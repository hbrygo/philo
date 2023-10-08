/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:27:39 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/06 14:09:50 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// number_of_philosophers : Le nombre de philosophes, mais aussi le nombre
// de fourchettes.

// time_to_die (en millisecondes) : Si un philosophe n’a pas commencé à manger
// time_to_die millisecondes après le début de son précédent repas ou depuis le
// début de la simulation, il meurt.

// time_to_eat (en millisecondes) : Le temps qu’un philosophe prend à manger.
// Pendant ce temps, un philosophe doit garder ses deux fourchettes.

// time_to_sleep (en millisecondes) : Le temps qu’un philosophe passe à dormir.

// number_of_times_each_philosopher_must_eat (argument optionnel) : Si tous
// les philosophes ont mangé au moins number_of_times_each_philosopher_must_eat
// fois, la simulation prend fin. Si cet argument n’est pas spécifié, alors la simulation prend fin à la mort d’un philosophe.

void	ft_init_philo(t_philo_state *p)
{
	p->thinking = 1;
	p->state = THINK;
	if (p->philo->id % 2 == 0)
		ft_sleep(p->philo->time_to_eat, p);
	gettimeofday(&p->last_eat, NULL);
}

void	*ft_routine(void *v_philo)
{
	t_philo_state	p;

	p.philo = (t_philo *)v_philo;
	ft_init_philo(&p);
	while (1)
	{
		if (ft_is_dead(p.philo->mut_dead, p.philo->death))
			break ;
		if (ft_eat(&p))
			break;
		if (philo_sleep(&p))
			break;
		if (ft_think(&p))
			break;
		if (ft_death(&p))
			break ;
	}
	return (NULL);
}

static int	ft_watchdog(t_philo_param *philo)
{
	int	ret;

	ret = 0;
	while (1)
	{
		if (pthread_mutex_lock(&philo->mut_dead_param))
			break ;
		if (philo->death == 1)
			ret = 1;
		pthread_mutex_unlock(&philo->mut_dead_param);
		if (ret == 1)
			break ;
		usleep(100);
	}
	return (1);
}

int	ft_philo_destructor(t_philo_param *ptr, int ret)
{
	int	i;

	i = 0;
	while (ptr->philos && ptr->philos[i].id)
		if (pthread_mutex_destroy(&ptr->philos[i++].fork))
			ret = 1;
	if (pthread_mutex_destroy(&ptr->printing))
		ret = 1;
	if (pthread_mutex_destroy(&ptr->mut_dead_param))
		ret = 1;
	free(ptr->philos);
	free(ptr->thread_p);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_philo_param	p;
	int				i;

	p.start = get_time();
	i = -1;
	if (ft_init(&p, argc, argv) == -1)
		return (1);
	p.philos = ft_create_philo(&p, 0);
	while (++i < p.nb_philo && p.philos)
	{
		if (i == p.nb_philo)
			p.philos[i].next = &p.philos[0];
		p.philos[i].next = &p.philos[i + 1];
		if (pthread_create(&p.thread_p[i], NULL, ft_routine,
				(void *)&p.philos[i]))
			break ;
	}
	i = 0;
	while (i < p.nb_philo && p.nb_to_eat != -1 && p.philos)
		if (pthread_join(p.thread_p[i++], NULL))
			return (ft_philo_destructor(&p, 1));
	while (i < p.nb_philo && p.nb_to_eat == -1 && p.philos)
		if (pthread_detach(p.thread_p[i++]))
			return (ft_philo_destructor(&p, 1));
	if (p.philos && p.nb_to_eat == -1 && ft_watchdog(&p))
		i = 0;
	return (ft_philo_destructor(&p, (!p.philos)));
}
