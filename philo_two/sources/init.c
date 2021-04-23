/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 06:36:00 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/23 13:38:38 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	str_error(char *str, int ret)
{
	printf("%s\n", str);
	return (ret);
}

void	init_mutex(t_philo **ph)
{
	int	i;

	i = 0;
	while (i < (*ph)->num_of_philo + 2)
	{
		pthread_mutex_init(&(*ph)->m[i], NULL);
		i++;
	}
}

void	init_philo(t_philo **ph)
{
	int	i;
	int	l;
	int	r;

	i = 0;
	l = 0;
	r = 1;
	while (i < (*ph)->num_of_philo)
	{
		(*ph)[i].left_fork = l;
		(*ph)[i].right_fork = r;
		l++;
		if (r == (*ph)->num_of_philo - 1)
			r = 0;
		else
			r++;
		i++;
	}
}

int	init_struct(t_philo **ph, char **argv)
{
	int	i;
	int	num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!num_ph)
		return (str_error("error: incorrect format arguments", -1));
	(*ph)->t = (pthread_t *)malloc(sizeof(pthread_t) * num_ph);
	if (!(*ph)->t)
		return (str_error("error: malloc problem", -1));
	(*ph)->m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_ph + 2);
	if (!(*ph)->m)
		return (str_error("error: malloc problem", -1));
	while (i < num_ph)
	{
		(*ph)[i].m = (*ph)[0].m;
		if (parse(&(*ph)[i++], argv))
			return (-1);
	}
	init_mutex(ph);
	init_philo(ph);
	return (0);
}
