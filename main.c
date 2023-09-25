/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:27:39 by hubrygo           #+#    #+#             */
/*   Updated: 2023/09/25 18:36:51 by hubrygo          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Argument\n"));
	if (ft_init(&data, argc, argv) != 0)
		return (1);
	ft_init(&data, argc, argv);
	return (0);
}
