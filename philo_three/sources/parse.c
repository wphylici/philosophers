/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 06:39:59 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/25 11:22:56 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	check_symb(char **argv)
{
	int	i;
	int	j;

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
	ph->count_eat_each = 0;
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
		return (str_error("error: incorrect format arguments", -1));
	return (0);
}
