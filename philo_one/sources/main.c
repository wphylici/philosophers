/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/21 16:55:45 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	check_die(t_philo *ph)
{
	size_t	tmp;

	if (!ph->count_eat)
		tmp = 0;
	else
		tmp = get_time() - ph->time_last_eat;
	if ((size_t)ph->time_to_die < tmp)
	{
		block_print = 1;
		!death_flag && printf("[%lu] ph %d is die\n",
		get_time() - ph->start_time,
		ph->n + 1);
		death_flag = 1;
		return (-1);
	}
	upgrade_usleep(0.1);
	return (0);
}

void	*proc(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	ph->time_last_eat = ph->start_time;
	while (ph->h_m_must_eat)
	{
		pthread_mutex_lock(&ph->m[ph->left_fork]);
		print_logs("take left fork", ph);
		pthread_mutex_lock(&ph->m[ph->right_fork]);
		print_logs("take right fork", ph);
		ph->time_last_eat = get_time();
		++ph->count_eat;
		ph->h_m_must_eat--;
		print_logs("is eating", ph);
		upgrade_usleep(ph->time_to_eat);
		pthread_mutex_unlock(&ph->m[ph->right_fork]);
		pthread_mutex_unlock(&ph->m[ph->left_fork]);
		print_logs("is sleeping", ph);
		upgrade_usleep(ph->time_to_sleep);
		print_logs("is thinking", ph);
	}
	return (NULL);
}

void	*die(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	while (1)
	{
		if (check_die(ph))
			break ;
	}
	return (NULL);
}

void	start(t_philo *ph)
{
	size_t			time;
	int				i;

	i = 0;
	while (i < ph->num_of_philo)
	{
		if (i == 0)
			time = get_time();
		ph[i].n = i;
		ph[i].start_time = time;
		if (i % 2 == 1)
			upgrade_usleep(0.01);
		pthread_create(&ph->t[i], NULL, proc, (void *)&ph[i]);
		pthread_create(&ph->t[i], NULL, die, (void *)&ph[i]);
		i++;
	}
	i = 0;
	while (i < ph->num_of_philo)
		pthread_join(ph->t[i++], NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;

	if (argc < 5 || argc > 6)
	{
		printf("error: incorrect number of arguments\n");
		return (0);
	}
	else
	{
		ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!ph)
			return (-1);
		if (init_struct(&ph, argv))
			return (-1);
		start(ph);
	}
	return (0);
}
