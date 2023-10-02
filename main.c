/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:27:39 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/01 16:58:43 by hubrygo          ###   ########.fr       */
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

// int	ft_eat(t_data *data)
// {
// 	int	time;

// 	time = get_time();
// }

void	*ft_routine(void *v_data)
{
	t_data *data;

	data = (t_data *)v_data;
	// while (1)
	// {
	// 	// if (ft_is_dead(&data->m_dead, &data->dead) == 1)
	// 	// 	break ;
	// 	// if (data->philos->status == EAT && ft_eat(data))
	// 	// 	break ;
	// 	// else if (data->philos->status == SLEEP && ft_sleep(data))
	// 	// 	break ;
	// 	// else if (data->philos->status == THINK && ft_think(data))
	// 	// 	break ;
	// 	// if (ft_dead(data))
	// 	// 	break ;
	// }
	// ft_philo_end(data);
	return (0);
	/*faire les routines et ne pas oublier de mutex_lock / mutex_unloch a chaque fois les fork*/
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf("Error: Argument\n"));
	if (ft_init(&data, argc, argv) != 0)
		return (1);
	while (i < data.nb_of_philo)
	{
		if (pthread_create(&data.thread_id[i], NULL, ft_routine, (void *)&data.philos[i]))
			break ;
		i++;
	}
	/*join tout les thread si nb_of_meal != 0*/
	/*detach tout les thread si nb_of_meal == 0*/
	ft_sleep(1000, &data);
	return (0);
}
