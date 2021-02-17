/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:40:46 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/17 02:44:42 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

typedef struct	s_philo
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			h_m_must_eat;

}				t_philo;

pthread_mutex_t  mutex[];


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
	// 	printf("error: incorrect format argument\n");
}

pthread_t t1, t2;

void *print(void *str)
{
	int i;

	i = -1;
	while (++i < 20)
	{
		printf("%s\n", (char *)str);
	}
	return NULL;
}

void	start(t_philo *ph)
{
	int		i;
	char	*str = "1 1 1 1 1 1 1 1 1 1";

	i = 0;
	pthread_mutex_init(&mutex1, NULL);
	// while (ph->num_of_philo > i)
	// {
		pthread_create(&t1, NULL, print, (void *)str);
		pthread_join(t1, NULL);
		write(1, "exit\n", 5);
	// }
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
