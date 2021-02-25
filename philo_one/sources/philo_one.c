/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/24 13:15:34 by wphylici         ###   ########.fr       */
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

}					t_philo;

typedef struct		s_data
{
	pthread_t 		*t;
	pthread_mutex_t	*m;
	t_philo			*ph;

}					t_data;

void	parse(t_data *data, char **argv)
{
	data->ph->num_of_philo = ft_atoi(argv[1]);
	// ph->time_to_die = ft_atoi(argv[2]);
	// ph->time_to_eat = ft_atoi(argv[3]);
	// ph->time_to_sleep = ft_atoi(argv[4]);
	// ph->h_m_must_eat = ft_atoi(argv[5]);
	// if (ph->num_of_philo < 2 || ph->time_to_die < 1 ||
	// ph->time_to_eat < 1 || ph->time_to_sleep < 1 ||
	// ph->h_m_must_eat < 1)
	// printf("error: incorrect format argument\n");
}

void	*proc(void *str)
{
	int i;
	t_data *data;

	data = (t_data *)str;
	while (1)
	{
		printf("ph %d take fork\n", data->n);

	}
	return NULL;
}

void	init_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->ph->num_of_philo)
	{
		pthread_mutex_init(&data->m[i], NULL);
		i++;
	}
}

void	init_philo(t_data *data)
{
	int i;
	int l;
	int	r;

	i = 0;
	l = 0;
	r = 1;
	while (i < data->ph->num_of_philo)
	{
		data->ph[i].left_fork = l;
		data->ph[i].right_fork = r;
		l++;
		if (r == data->ph->num_of_philo - 1)
			r = 0;
		else
			r++;
		i++;
	}
}

void	start(t_data *data)
{
	int	i;

	i = 0;
	init_mutex(data);
	init_philo(data);
	while (i < data->ph->num_of_philo)
	{
		data->ph[i].n = i;
		pthread_create(&data->t[i], NULL, proc, (void *)data);
		pthread_join(data->t[i], NULL);
		i++;
	}
}

void	init_struct(t_data *data, char **argv)
{
	int i;
	int num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!(data->t = (t_data *)malloc(sizeof(t_data) * num_ph)))
		exit(EXIT_FAILURE);
	if (!(data->m = (t_data *)malloc(sizeof(t_data) * num_ph)))
		exit(EXIT_FAILURE);
	if (!(data->ph = (t_data *)malloc(sizeof(t_data) * num_ph)))
		exit(EXIT_FAILURE);
	while (i < num_ph)
		parse(&data->ph[i++], argv);
}

int		main(int argc, char **argv)
{
	t_data data;

	//if (argc < 5 || argc > 6)
	//	printf("error: incorrect number of arguments\n");
	// else
	// {
	if (argc > 1)
	{
		init_struct(&data, argv);
		start(&data);
	}
	return (0);
}
