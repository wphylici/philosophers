/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 06:36:00 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 21:09:18 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	str_error(char *str, int ret)
{
	printf("%s\n", str);
	return (ret);
}

void	ft_sem_close(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->num_of_philo)
		sem_close(&ph->sem->forks_sem[i]);
	sem_close(ph->sem->print_sem);
}

void	init_sem(t_philo *ph, int num_ph)
{
	int	i;

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/waiter");
	ph->sem->forks_sem = sem_open("/forks", O_CREAT, S_IRWXU, num_ph);
	ph->sem->print_sem = sem_open("/print", O_CREAT, S_IRWXU, 1);
	ph->sem->waiter = sem_open("/waiter", O_CREAT, S_IRWXU, 1);
}

int	init_struct(t_philo *ph, char **argv)
{
	int	i;
	int	num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!num_ph)
		return (str_error("error: incorrect format arguments", -1));
	ph->t = (pthread_t *)malloc(sizeof(pthread_t) * num_ph);
	if (!ph->t)
		return (str_error("error: malloc problem", -1));
	init_sem(ph, num_ph);
	while (i < num_ph)
	{
		ph[i].sem = ph[0].sem;
		if (parse(&ph[i], argv))
			return (-1);
		i++;
	}
	return (0);
}
