/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:37:54 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/27 03:35:09 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

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

void	print_logs(char *str, t_philo *ph)
{
	if (!g_death_flag)
	{
		sem_wait(ph->sem->print_sem);
		if (!g_death_flag)
			printf("\e[0;93m[%lu]\e[0m ph %d %s\n", get_time() - ph->start_time,
				ph->n + 1, str);
		sem_post(ph->sem->print_sem);
	}
}

void	my_free(t_philo *ph)
{
	if (ph)
	{
		if (ph->t)
			free(ph->t);
		free(ph);
	}
}
