/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:37:54 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 12:19:23 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

unsigned int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	long long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '0')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		res = (res * 10) + (str[i++] - '0');
	if (i >= 19)
	{
		if (neg == 1)
			return (-1);
		else if (i > 19)
			return (0);
	}
	return (res * neg);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	upgrade_usleep(double msec)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(100);
}

void	ft_sem_close(t_philo *ph)
{
	int	i;

	i = 0;
	if (ph->sem->forks_sem && ph->sem->last_eat_sem && ph->sem->print_sem
		&& ph->sem->waiter)
	{
		while (i < ph->num_of_philo)
			sem_close(&ph->sem->forks_sem[i++]);
		sem_close(ph->sem->last_eat_sem);
		sem_close(ph->sem->print_sem);
		sem_close(ph->sem->waiter);
	}
}

void	my_exit(char *error, t_philo *ph)
{
	if (ph)
	{
		ft_sem_close(ph);
		if (ph->t)
			free(ph->t);
		if (ph->sem)
			free(ph->sem);
		if (ph->pid)
			free(ph->pid);
		free(ph);
	}
	if (error)
	{
		printf("%s\n", error);
		exit(EXIT_FAILURE);
	}
	exit (EXIT_SUCCESS);
}
