/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:44:11 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 21:08:49 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_sem
{
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*waiter;
}					t_sem;

typedef struct s_philo
{
	int				time_to_die;
	int				time_to_eat;
	int				num_of_philo;
	int				time_to_sleep;
	int				h_m_must_eat;
	int				count_eat_each;
	int				n;
	size_t			time_last_eat;
	size_t			start_time;
	pthread_t		*t;
	t_sem			*sem;
}					t_philo;

int					g_block_print;
int					g_death_flag;
int					g_count_eat_total;

unsigned int		ft_atoi(const char *str);
size_t				get_time(void);
void				upgrade_usleep(double msec);
int					init_struct(t_philo *ph, char **argv);
void				print_logs(char *str, t_philo *ph);
int					parse(t_philo *ph, char **argv);
void				my_free(t_philo *ph);
int					str_error(char *str, int ret);
void				ft_sem_close(t_philo *ph);

#endif
