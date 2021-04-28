/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 10:58:04 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*proc(t_philo *ph)
{
	ph->time_last_eat = ph->start_time;
	while (ph->count_eat_each != ph->h_m_must_eat)
	{
		sem_wait(ph->sem->waiter);
		sem_wait(ph->sem->forks_sem);
		print_logs("take left fork", ph);
		sem_wait(ph->sem->forks_sem);
		print_logs("take right fork", ph);
		sem_post(ph->sem->waiter);
		sem_wait(ph->sem->last_eat_sem);
		ph->time_last_eat = get_time();
		sem_post(ph->sem->last_eat_sem);
		++ph->count_eat_each;
		print_logs("is eating", ph);
		upgrade_usleep(ph->time_to_eat);
		sem_post(ph->sem->forks_sem);
		sem_post(ph->sem->forks_sem);
		print_logs("is sleeping", ph);
		upgrade_usleep(ph->time_to_sleep);
		print_logs("is thinking", ph);
	}
	exit(21);
}

int 	start(t_philo *ph)
{
	int	i;

	i = 0;
	pthread_create(ph->t, NULL, check_status, (void *)ph);
	proc(ph);
	if (ph->n % 2 == 1)
		upgrade_usleep(0.01);
	return (0);
}

void 	wait_fork(t_philo *ph)
{
	int	i;
	int	status;
	int	count_eat;

	i = -1;
	count_eat = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 21)
		{
			count_eat++;
			if (count_eat == ph->num_of_philo)
				break ;
		}
		else if (status == 42)
			break ;
	}
	while (++i < ph->num_of_philo)
		kill(ph->pid[i], SIGTERM);
	sem_post(ph->sem->print_sem);
}

void	forking(t_philo *ph)
{
	int		i;
	size_t	start_time;

	i = -1;
	start_time = get_time();
	while (++i < ph->num_of_philo)
	{
		ph->pid[i] = fork();
		if (ph->pid[i] < 0)
			my_exit("error: fork problem", ph);
		else if (ph->pid[i] == 0)
		{
			ph[i].start_time = start_time;
			ph[i].n = i;
			start(&ph[i]);
		}
	}
	wait_fork(ph);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;

	ph = NULL;
	if (argc < 5 || argc > 6)
		my_exit("error: incorrect number of arguments", ph);
	else
	{
		ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!ph)
			my_exit(NULL, ph);
		ph->sem = (t_sem *)malloc(sizeof(t_sem));
		if (!ph->sem)
			my_exit(NULL, ph);
		init_struct(ph, argv);
		forking(ph);
	}
	my_exit(NULL, ph);
	return (0);
}
