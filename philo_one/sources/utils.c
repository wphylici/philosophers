/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:37:54 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/21 06:44:35 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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

int	upgrade_usleep(double msec)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(100);
	return (0);
}

void	print_logs(char *str, t_philo *ph)
{
	if (!block_print)
	{
		pthread_mutex_lock(&ph->m[ph->print_mutext]);
		printf("[%lu] ph %d %s\n", get_time() - ph->start_time, ph->n + 1, str);
		pthread_mutex_unlock(&ph->m[ph->print_mutext]);
	}
}
