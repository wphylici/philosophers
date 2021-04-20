/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:44:11 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/20 05:26:47 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct		s_philo
{
	int	time_to_die;
	int	time_to_eat;
	int	num_of_philo;
	int	time_to_sleep;
	int	h_m_must_eat;
	int	count_eat;
	int	n;
	int left_fork;
    int	right_fork;
	int	print_mutext;
	int				death_flag;
	size_t			time_last_eat;
	size_t			start_time;
	pthread_t 		*t;
	pthread_mutex_t	*m;

}					t_philo;

unsigned int		ft_atoi(const char *str);

#endif
