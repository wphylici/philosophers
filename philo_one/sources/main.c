/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/20 05:35:28 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	parse(t_philo *ph, char **argv)
{
	check_symb()
	ph->num_of_philo = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	ph->print_mutext = ph->num_of_philo;
	ph->count_eat = 0;
	ph->death_flag = 0;
	if (!argv[5])
		ph->h_m_must_eat = -1;
	else
		ph->h_m_must_eat = ft_atoi(argv[5]);
	if (ph->num_of_philo < 2 || ph->num_of_philo >= INT_MAX ||
		ph->time_to_die < 1 || ph->time_to_die >= INT_MAX ||
		ph->time_to_eat < 1 || ph->time_to_eat >= INT_MAX ||
		ph->time_to_sleep < 1 || ph->time_to_sleep >= INT_MAX ||
		ph->h_m_must_eat < -1 || ph->h_m_must_eat >= INT_MAX)
	{
		printf("error: incorrect format arguments\n");
		return (-1);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_logs(char *str, t_philo *ph)
{
	pthread_mutex_lock(&ph->m[ph->print_mutext]);
	printf("[%lu] ph %d %s\n", get_time() - ph->start_time, ph->n + 1, str);
	if (!ph->death_flag)
		pthread_mutex_unlock(&ph->m[ph->print_mutext]);

}

int	check_die(t_philo *ph);

int upgrade_usleep(double msec, t_philo *ph)
{
	size_t start;

	(void)ph;
	start = get_time();
	while (get_time() - start < msec)
	{
		// if (check_die(ph))
		// {
		// 	exit (0);
		// }
		usleep(100);
	}
	return (0);
}

int	check_die(t_philo *ph)
{
	size_t tmp;

	if (!ph->count_eat)
		tmp = 0;
	else
		tmp = get_time() - ph->time_last_eat;
	if ((size_t)ph->time_to_die < tmp)
	{
		ph->death_flag = 1;
		print_logs("is dead", ph);
		return (-1);
	}
	upgrade_usleep(0.1, ph);
	return (0);
}

void	*proc(void *ptr)
{
	t_philo *ph;

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

		upgrade_usleep(ph->time_to_eat, ph);

		pthread_mutex_unlock(&ph->m[ph->right_fork]);
		pthread_mutex_unlock(&ph->m[ph->left_fork]);

		print_logs("is sleeping", ph);

		upgrade_usleep(ph->time_to_sleep, ph);
		print_logs("is thinking", ph);
	}
	return (NULL);
}

void	init_mutex(t_philo **ph)
{
	int i;

	i = 0;
	while (i <	(*ph)->num_of_philo + 1)
	{
		pthread_mutex_init(&(*ph)->m[i], NULL);
		i++;
	}
}

void	init_philo(t_philo **ph)
{
	int i;
	int l;
	int r;

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

void	*die(void *ptr)
{
	t_philo *ph;

	ph = (t_philo *)ptr;

	while (1)
	{
		if (check_die(ph))
		{
			exit (EXIT_FAILURE);
		}
	}
	return (NULL);
}

void	start(t_philo *ph)
{
	size_t 			time;
	int	i;

	i = 0;
	while (i < ph->num_of_philo)
	{
		if (i == 0)
			time = get_time();
		ph[i].n = i;
		ph[i].start_time = time;
		if (i % 2 == 1) // ???
			upgrade_usleep(0.01, ph);;
		pthread_create(&ph->t[i], NULL, proc, (void *)&ph[i]);
		pthread_create(&ph->t[i], NULL, die, (void *)&ph[i]);
		i++;
	}
	i = 0;
	while (i < ph->num_of_philo)
		pthread_join(ph->t[i++], NULL);
}

int	init_struct(t_philo **ph, char **argv)
{
	int i;
	int num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!((*ph)->t = (pthread_t *)malloc(sizeof(pthread_t) * num_ph)))
		return (-1);
	if (!((*ph)->m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_ph + 1)))
		return (-1);
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

int		main(int argc, char **argv)
{
	t_philo *ph;

	if (argc < 5 || argc > 6)
	{
		printf("error: incorrect number of arguments\n");
		return (0);
	}
	else
	{
		if (!(ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]))))
			return (-1);
		if (init_struct(&ph, argv))
			return (-1);
		start(ph);
	}
	return (0);
}