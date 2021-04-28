/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 21:18:58 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	check_die(t_philo *ph)
{
	size_t	tmp;

	if (!ph->count_eat_each)
		tmp = 0;
	else
		tmp = get_time() - ph->time_last_eat;
	if ((size_t)ph->time_to_die < tmp)
	{
		g_death_flag = 1;
		!g_block_print && printf("\e[0;93m[%lu]\e[0m ph %d \e[0;91mis die\e[0m\n",
		get_time() - ph->start_time, ph->n + 1);
		g_block_print = 1;
		return (-1);
	}
	usleep(10);
	return (0);
}

void	*proc(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	ph->time_last_eat = ph->start_time;
	while (ph->count_eat_each != ph->h_m_must_eat && !g_death_flag)
	{
		sem_wait(ph->sem->waiter);
		sem_wait(ph->sem->forks_sem);
		print_logs("take left fork", ph);
		sem_wait(ph->sem->forks_sem);
		print_logs("take right fork", ph);
		sem_post(ph->sem->waiter);
		ph->time_last_eat = get_time();
		++ph->count_eat_each;
		++g_count_eat_total;
		print_logs("is eating", ph);
		upgrade_usleep(ph->time_to_eat);
		sem_post(ph->sem->forks_sem);
		sem_post(ph->sem->forks_sem);
		print_logs("is sleeping", ph);
		upgrade_usleep(ph->time_to_sleep);
		print_logs("is thinking", ph);
	}
	return (NULL);
}

int	check_status(t_philo *ph)
{
	int	i;

	i = 0;
	while (g_count_eat_total / ph->num_of_philo != ph->h_m_must_eat)
	{
		if (i == ph->num_of_philo - 1)
			i = 0;
		if (check_die(&ph[i]))
			return (-1);
		++i;
	}
	return (-1);
}

int 	start(t_philo *ph)
{
	size_t			time;
	int				i;

	i = 0;
	time = get_time();
	while (i < ph->num_of_philo)
	{
		ph[i].n = i;
		ph[i].start_time = time;
		pthread_create(&ph->t[i], NULL, proc, (void *)&ph[i]);
		++i;
	}
	if (check_status(ph))
		return (-1);
	i = 0;
	while (i < ph->num_of_philo)
		pthread_join(ph->t[i++], NULL);
	ft_sem_close(ph);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;

	ph = NULL;
	if (argc < 5 || argc > 6)
		return (str_error("error: incorrect number of arguments", -1));
	else
	{
		ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!ph)
			return (-1);
		ph->sem = (t_sem *)malloc(sizeof(t_sem));
		if (!ph->sem)
			return (-1);
		if (init_struct(ph, argv))
		{
			my_free(ph);
			return (-1);
		}
		start(ph);
	}
	my_free(ph);
	return (0);
}
