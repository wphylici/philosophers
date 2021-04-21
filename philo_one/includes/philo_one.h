/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:44:11 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/21 06:40:27 by wphylici         ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				num_of_philo;
	int				time_to_sleep;
	int				h_m_must_eat;
	int				count_eat;
	int				n;
	int 			left_fork;
    int				right_fork;
	int				print_mutext;
	size_t			time_last_eat;
	size_t			start_time;
	pthread_t 		*t;
	pthread_mutex_t	*m;

}					t_philo;

int block_print;
int death_flag;

unsigned int		ft_atoi(const char *str);
size_t				get_time(void);
int 				upgrade_usleep(double msec);
int					init_struct(t_philo **ph, char **argv);
void				print_logs(char *str, t_philo *ph);
int					parse(t_philo *ph, char **argv);

#endif
