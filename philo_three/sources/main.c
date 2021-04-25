/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/25 17:48:33 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	check_die(t_philo *ph)
{
	size_t	tmp;

	if (!ph->count_eat_each)
		tmp = 0;
	else
	{
		sem_wait(ph->sem->last_eat_sem);
		tmp = get_time() - ph->time_last_eat;
		sem_post(ph->sem->last_eat_sem);
	}
	if ((size_t)ph->time_to_die < tmp)
	{
		g_death_flag = 1;
		!g_block_print && printf("\e[0;93m[%lu]\e[0m ph %d \e[0;91mis die\e[0m\n",
		get_time() - ph->start_time, ph->n + 1);
		g_block_print = 1;
		return (-1);
	}
	return (0);
}

void	*proc(t_philo *ph)
{
	int res = -1;

	ph->time_last_eat = ph->start_time;
	while (ph->h_m_must_eat && !g_death_flag)
	{

		sem_getvalue(ph->sem->forks_sem, res);
		printf("res before - %d\n", res);
		sem_wait(ph->sem->take_forks_sem);
		sem_wait(ph->sem->forks_sem);
		print_logs("take left fork", ph);
		sem_wait(ph->sem->forks_sem);
		print_logs("take right fork", ph);
		sem_post(ph->sem->take_forks_sem);
		sem_wait(ph->sem->last_eat_sem);
		ph->time_last_eat = get_time();
		sem_post(ph->sem->last_eat_sem);
		++ph->count_eat_each;
		++g_count_eat_total;
		--ph->h_m_must_eat;
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

void	*check_status(void *ptr)
{
	t_philo *ph;
	int	i;

	i = 0;
	ph = (t_philo *)ptr;
	while (ph->count_eat_each != ph->tmp_h_m_must_eat && !g_death_flag)
	{
		if (check_die(ph))
			exit(42);
		upgrade_usleep(0.1);
	}
	exit(21);
}

int 	start(t_philo *ph)
{
	size_t			time;
	int				i;

	i = 0;
	pthread_create(&ph->t[0], NULL, check_status, (void *)&ph[i]);
	while (1)
	{
		if (ph->n % 2 == 1)
			upgrade_usleep(0.1);
		time = get_time();
		ph->start_time = time;
		proc(ph);
	}
	// while (i < ph->num_of_philo)
	// 	sem_close(&ph->sem->forks_sem[i++]);
	return (0);
}

void	init(t_philo *ph)
{
	int i;
	int j;
	int check;
	int status;

	i = -1;
	j = -1;
	check = 0;

	while (++i < ph->num_of_philo)
	{
		ph->pid[i] = fork();
		if (ph->pid[i] < 0)
			return ;
		else if (ph->pid[i] == 0)
		{
			ph[i].n = i;
			start(&ph[i]);
		}
	}
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 21)
		{
			check++;
			if (check == ph->num_of_philo)
				break ;
		}
		else if (status == 42)
			break;
	}
	while (++j < ph->num_of_philo)
		kill(ph->pid[j], SIGTERM);
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
		if (init_struct(&ph, argv))
		{
			//my_free(ph);
			return (-1);
		}
		init(ph);
	}
	// my_free(ph);
	return (0);
}
