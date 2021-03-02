/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/28 18:36:43 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

typedef struct		s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				h_m_must_eat;
	unsigned int	n;
	unsigned int 	left_fork;
    unsigned int	right_fork;
	pthread_t 		*t;
	pthread_mutex_t	*m;

}					t_philo;

void	parse(t_philo *ph, char **argv)
{
	ph->num_of_philo = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]) * 1000;
	ph->time_to_eat = ft_atoi(argv[3]) * 1000;
	ph->time_to_sleep = ft_atoi(argv[4]) * 1000;
	// ph->h_m_must_eat = ft_atoi(argv[5]);
	// if (ph->num_of_philo < 2 || ph->time_to_die < 1 ||
	// 	ph->time_to_eat < 1 || ph->time_to_sleep < 1 ||
	// 	ph->h_m_must_eat < 1)
	// 	printf("error: incorrect format argument\n");
}

void	time_die(t_philo *ph)
{
	static time_t	str_time = 0;
	static int		count = 0;

	if (time(0) - str_time >= 1)
	{
		str_time = time(0);
	}
	else
		count++;
}

int		check_time(t_philo *ph)
{
	struct timeval tv;
	struct timezone tz;
	static time_t time_start;

	gettimeofday(&tv,  &tz);
	time_start = tv.tv_usec;
	if (tv.tv_usec - time_start > ph->time_to_die)
		return (-1);
	return (0);
}


void	*proc(void *str)
{
	int i;
	t_philo *ph;

	ph = (t_philo *)str;
	while (1)
	{
		if (check_time(ph))
		{
			printf("ph %d is dead\n", ph->n);
			exit(0);
		}
		pthread_mutex_lock(&ph->m[ph->left_fork]);
		pthread_mutex_lock(&ph->m[ph->right_fork]);

		printf("ph %d take fork\n", ph->n);
		printf("ph %d is eating\n", ph->n);

		usleep(ph->time_to_eat);
		pthread_mutex_unlock(&ph->m[ph->right_fork]);
		pthread_mutex_unlock(&ph->m[ph->left_fork]);

		printf("ph %d finished dinner\n", ph->n);
		printf("ph %d is sleeping\n", ph->n);
		usleep(ph->time_to_sleep);
	}
	return NULL;
}

void	init_mutex(t_philo *ph)
{
	int i;

	i = 0;
	while (i < ph->num_of_philo)
	{
		pthread_mutex_init(&ph->m[i], NULL);
		i++;
	}
}

void	init_philo(t_philo *ph)
{
	int i;
	int l;
	int	r;

	i = 0;
	l = 0;
	r = 1;
	while (i < ph->num_of_philo)
	{
		ph[i].left_fork = l;
		ph[i].right_fork = r;
		l++;
		if (r == ph->num_of_philo - 1)
			r = 0;
		else
			r++;
		i++;
	}
}

void	start(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->num_of_philo)
	{
		ph[i].n = i;
		pthread_create(&ph->t[i], NULL, proc, (void *)&ph[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < ph->num_of_philo)
	{
		pthread_join(ph->t[i], NULL);
		i++;
	}
}

void	init_struct(t_philo *ph, char **argv)
{
	int i;
	int num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!(ph->t = (pthread_t *)malloc(sizeof(pthread_t) * num_ph)))
		exit(EXIT_FAILURE);
	if (!(ph->m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_ph)))
		exit(EXIT_FAILURE);
	while (i < num_ph)
	{
		ph[i].m = ph[0].m;
		parse(&ph[i++], argv);
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
		init_struct(ph, argv);
		start(ph);
	}
	return (0);
}
