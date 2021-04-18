/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/18 19:43:57 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int				flag_print;

void	parse(t_philo *ph, char **argv)
{
	ph->num_of_philo = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	ph->last_eat_mutex = ph->num_of_philo;
	flag_print = 0;
	ph->count_eat = 0;
	// ph->h_m_must_eat = ft_atoi(argv[5]);
	// if (ph->num_of_philo < 2 || ph->time_to_die < 1 ||
	// 	ph->time_to_eat < 1 || ph->time_to_sleep < 1 ||
	// 	ph->h_m_must_eat < 1)
	// 	printf("error: incorrect format argument\n");
}

// int upgrade_usleep(size_t msec)
// {
// 	size_t start;
// 	size_t stop;
// 	size_t diff;

// 	start = get_time();
// 	stop = get_time();
// 	diff = stop - start;
// 	while (diff < msec)
// 	{
// 		stop = get_time();
// 		diff = stop - start;
// 		usleep(10);
// 	}
// 	return (0);
// }

size_t	get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_logs(char *str, t_philo *ph)
{
	if (!flag_print)
		printf("[%lu] ph %d %s\n", get_time() - ph->start_time, ph->n, str);
}

int	check_die(t_philo *ph)
{
	size_t tmp;

	if (!ph->count_eat)
		tmp = 0;
	else
		tmp = get_time() - ph->time_last_eat;
	// printf("%d - tmp - %lu\n", ph->n, tmp);
	if (get_time() < ph->time_last_eat)
		printf("lalala");
	if (ph->time_to_die < tmp)
	{
		// printf("%u - get time - %lu\n", ph->n, get_time());
		// printf("%u - last eat time - %lu\n", ph->n, ph->time_last_eat);

		// printf("%d - tmp - %lu\n", ph->n, tmp);
		print_logs("is dead", ph);
		flag_print = 1;
		return (-1);
	}
	usleep(50);
	return (0);
}

int upgrade_usleep(size_t msec, t_philo *ph)
{
	size_t start;

	start = get_time();
	while (get_time() - start < msec)
	{
		// if (check_die(ph))
		// {
		// 	return (1);
		// }
		usleep(100);
	}
	return (0);
}

void	*proc(void *ptr)
{
	int i;
	t_philo *ph;

	ph = (t_philo *)ptr;
	ph->time_last_eat = ph->start_time;
	while (1)
	{
		pthread_mutex_lock(&ph->m[ph->left_fork]);
		print_logs("take left fork", ph);
		pthread_mutex_lock(&ph->m[ph->right_fork]);
		print_logs("take right fork", ph);

		// pthread_mutex_lock(&ph->m[ph->last_eat_mutex]);
		// pthread_mutex_unlock(&ph->m[ph->last_eat_mutex]);
		// printf("%d - last meal time - %lu\n", ph->n, ph->time_last_eat - ph->start_time);
		++ph->count_eat;

		print_logs("is eating", ph);
		ph->time_last_eat = get_time();

		upgrade_usleep(ph->time_to_eat, ph);

		pthread_mutex_unlock(&ph->m[ph->right_fork]);
		pthread_mutex_unlock(&ph->m[ph->left_fork]);

		print_logs("finished dinner", ph);
		print_logs("is sleeping", ph);

		upgrade_usleep(ph->time_to_sleep, ph);
		//printf("ph %d is thinking\n", ph->n);
	}
	return (NULL);
}

void	init_mutex(t_philo **ph)
{
	int i;

	i = 0;
	while (i <	(*ph)->num_of_philo)
	{
		pthread_mutex_init(&(*ph)->m[i], NULL);
		i++;
	}
}

void	init_philo(t_philo **ph)
{
	int i;
	int l;
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

void	*die(void *ptr)
{
	int i;
	t_philo *ph;

	ph = (t_philo *)ptr;

	while (1)
	{
		if (check_die(ph))
		{
			// pthread_mutex_unlock(&ph->m[ph->left_fork]);
			exit(0);
		}
	}
	return (NULL);
}

void	start(t_philo *ph)
{
	size_t time;
	int	i;
	// pthread_t *t = malloc(sizeof(pthread_t) * ph->num_of_philo);

	i = 0;
	while (i < ph->num_of_philo)
	{
		if (i == 0)
			time = get_time();
		ph[i].n = i;
		ph[i].start_time = time;
		if (i % 2 == 1)
			usleep(10);
		pthread_create(&ph->t[i], NULL, proc, (void *)&ph[i]);
		pthread_create(&ph->t[i], NULL, die, (void *)&ph[i]);
		i++;
	}
	i = 0;
	// while (i < ph->num_of_philo)
	// {
	// 	ph[i].n = i;
	// 	pthread_create(&ph->t[i], NULL, die, (void *)&ph[i]);
	// 	upgrade_usleep(10, ph);
	// 	i++;
	// }
	// i = 0;
	while (i < ph->num_of_philo)
	{
		pthread_join(ph->t[i], NULL);
		i++;
	}
}

void	init_struct(t_philo **ph, char **argv)
{
	int i;
	int num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!((*ph)->t = (pthread_t *)malloc(sizeof(pthread_t) * num_ph)))
		exit(EXIT_FAILURE);
	if (!((*ph)->m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_ph + 1)))
		exit(EXIT_FAILURE);
	while (i < num_ph)
	{
		(*ph)[i].m = (*ph)[0].m;
		parse(&(*ph)[i++], argv);
	}
	init_mutex(ph);
	init_philo(ph);
}

int		main(int argc, char **argv)
{
	t_philo *ph;

	//if (argc < 5 || argc > 6)
	//	printf("error: incorrect number of arguments\n");
	// else
	// {
	if (!(ph = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]))))
		exit(EXIT_FAILURE);
	if (argc > 1)
	{
		init_struct(&ph, argv);
		start(ph);
	}
	return (0);
}
