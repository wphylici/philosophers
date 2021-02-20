/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/20 15:32:02 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

// typedef struct		s_data
// {
// 	pthread_t 		t;
// 	pthread_mutex_t	m;

// }					t_data;

typedef struct		s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				h_m_must_eat;
	int				n;
	pthread_t 		t;
	pthread_mutex_t	m;
	// t_data			*data;

}					t_philo;

void	parse(t_philo *ph, char **argv)
{
	ph->num_of_philo = ft_atoi(argv[1]);
	// ph->time_to_die = ft_atoi(argv[2]);
	// ph->time_to_eat = ft_atoi(argv[3]);
	// ph->time_to_sleep = ft_atoi(argv[4]);
	// ph->h_m_must_eat = ft_atoi(argv[5]);
	// if (ph->num_of_philo < 2 || ph->time_to_die < 1 ||
	// ph->time_to_eat < 1 || ph->time_to_sleep < 1 ||
	// ph->h_m_must_eat < 1)
	// printf("error: incorrect format argument\n");
}

void *proc(void *str)
{
	int i;
	t_philo *ph;

	ph = str;
	int lo;
	while (1)
	{
		printf("ph %d take fork\n", ph->n);
	}
	return NULL;
}

void	start(t_philo *ph)
{
	int				i;

	char	*str = "1 1 1 1 1 1 1 1 1 1";

	i = 0;
	//pthread_mutex_init(&m, NULL);
	//ph->t = (pthread_t *)malloc(sizeof(pthread_t));
	while (i < ph->num_of_philo)
	{
		ph->n = i;
		pthread_create(&ph[i].t, NULL, proc, (void *)ph);
		pthread_join(ph[i].t, NULL);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_philo ph[ft_atoi(argv[1])];

	//if (argc < 5 || argc > 6)
	//	printf("error: incorrect number of arguments\n");
	// else
	// {
	if (argc > 1)
	{
		parse(ph, argv);
		start(ph);
	}
	return (0);
}
