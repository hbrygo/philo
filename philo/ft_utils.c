/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:32:10 by hubrygo           #+#    #+#             */
/*   Updated: 2023/10/12 15:07:49 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(time_t end, t_rules *rules)
{
	time_t	wake_up;

	wake_up = get_time() + end;
	while (!(rules->dead))
	{
		if (get_time() >= wake_up)
			break ;
		usleep(50);
	}
}

void	ft_mut_print(int id, t_rules *rules, char *str)
{
	pthread_mutex_lock(&rules->state_write);
	if (!rules->dead)
		printf("%ld %d %s\n", get_time() - rules->start_time, id + 1, str);
	pthread_mutex_unlock(&rules->state_write);
}

static int	skip(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long int	result;
	long int	last;
	int			sign;

	result = 0;
	last = 0;
	sign = 1;
	str += skip((char *)str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		if (last > result && sign > 0)
			return (-1);
		else if (last > result && sign < 0)
			return (0);
		str++;
		last = result;
	}
	return (result * sign);
}
