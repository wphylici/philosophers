/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 06:36:00 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 10:55:57 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	init_sem(t_philo **ph, int num_ph)
{
	int	i;

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/waiter");
	sem_unlink("/print");
	sem_unlink("/last_eat");
	(*ph)->sem->forks_sem = sem_open("/forks", O_CREAT, S_IWUSR, num_ph);
	(*ph)->sem->waiter = sem_open("/waiter", O_CREAT, S_IWUSR, 1);
	(*ph)->sem->print_sem = sem_open("/print", O_CREAT, S_IWUSR, 1);
	(*ph)->sem->last_eat_sem = sem_open("/last_eat", O_CREAT, S_IWUSR, 1);
}

int	init_struct(t_philo *ph, char **argv)
{
	int	i;
	int	num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (num_ph <= 0)
		my_exit("error: incorrect format arguments", ph);
	ph->t = (pthread_t *)malloc(sizeof(pthread_t));
	if (!ph->t)
		my_exit("error: malloc problem", ph);
	ph->pid = (pid_t *)malloc(sizeof(pid_t) * num_ph);
	if (!ph->pid)
		my_exit("error: malloc problem", ph);
	init_sem(&ph, num_ph);
	while (i < num_ph)
	{
		ph[i] = ph[0];
		parse(&ph[i++], argv);
	}
	return (0);
}
