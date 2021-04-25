/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 06:36:00 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/25 01:27:18 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	str_error(char *str, int ret)
{
	printf("%s\n", str);
	return (ret);
}

void	init_sem(t_philo **ph)
{
	int i;

	i = 0;
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("last_eat");
	ph[0]->forks_sem = sem_open("forks", O_CREAT, O_EXCL,  0600, (*ph)->num_of_philo);
	ph[0]->prin_sem = sem_open("print", O_CREAT, O_EXCL, 0600, 1);
	ph[0]->last_eat_sem = sem_open("last_eat", O_CREAT, O_EXCL, 0600, 1);
	while (i < (*ph)->h_m_must_eat)
	{
		(*ph)[i].prin_sem = (*ph)[0].prin_sem;
		(*ph)[i].last_eat_sem = (*ph)[0].last_eat_sem;
		(*ph)[i].forks_sem = (*ph)[0].forks_sem;
	}
}

int	init_struct(t_philo **ph, char **argv)
{
	int	i;
	int	num_ph;

	i = 0;
	num_ph = ft_atoi(argv[1]);
	if (!num_ph)
		return (str_error("error: incorrect format arguments", -1));
	(*ph)->t = (pthread_t *)malloc(sizeof(pthread_t) * num_ph);
	if (!(*ph)->t)
		return (str_error("error: malloc problem", -1));
	init_sem(ph);
	while (i < num_ph)
	{
		if (parse(&(*ph)[i++], argv))
			return (-1);
	}
	return (0);
}
