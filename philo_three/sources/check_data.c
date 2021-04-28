/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:55:06 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 10:57:07 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	print_logs(char *str, t_philo *ph)
{
	sem_wait(ph->sem->print_sem);
	if (ph->death_flag)
	{
		printf("\e[0;93m[%lu]\e[0m ph %d \e[0;91m%s\e[0m\n",
			get_time() - ph->start_time, ph->n + 1, str);
		exit(42);
	}
	printf("\e[0;93m[%lu]\e[0m ph %d %s\n", get_time() - ph->start_time,
		ph->n + 1, str);
	sem_post(ph->sem->print_sem);
}

int	check_die(t_philo *ph)
{
	size_t	tmp;

	if (!ph->count_eat_each)
		tmp = 0;
	else
		tmp = get_time() - ph->time_last_eat;
	if ((size_t)ph->time_to_die < tmp)
	{
		ph->death_flag = 1;
		print_logs("is die", ph);
		return (-1);
	}
	return (0);
}

void	*check_status(void *ptr)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = (t_philo *)ptr;
	while (1)
	{
		check_die(ph);
		upgrade_usleep(0.1);
	}
	return (NULL);
}
