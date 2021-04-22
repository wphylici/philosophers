/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 06:39:59 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/22 10:09:24 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int check_symb(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse(t_philo *ph, char **argv)
{
	ph->num_of_philo = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	ph->print_mutext = ph->num_of_philo;
	ph->last_eat_mutex = ph->num_of_philo + 1;
	ph->count_eat_each = 0;
	count_eat_total = 0;
	death_flag = 0;
	block_print = 0;
	if (!argv[5])
		ph->h_m_must_eat = -1;
	else
		ph->h_m_must_eat = ft_atoi(argv[5]);
	ph->tmp_h_m_must_eat = ph->h_m_must_eat;
	if (ph->num_of_philo < 2 || ph->num_of_philo >= INT_MAX
		|| ph->time_to_die < 1 || ph->time_to_die >= INT_MAX
		|| ph->time_to_eat < 1 || ph->time_to_eat >= INT_MAX
		|| ph->time_to_sleep < 1 || ph->time_to_sleep >= INT_MAX
		|| ph->h_m_must_eat < -1 || ph->h_m_must_eat >= INT_MAX
		|| check_symb(argv))
	{
		printf("error: incorrect format arguments\n");
		return (-1);
	}
	return (0);
}
