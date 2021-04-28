/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:44:11 by wphylici          #+#    #+#             */
/*   Updated: 2021/04/28 10:57:54 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_sem
{
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*last_eat_sem;
	sem_t			*waiter;
}				t_sem;

typedef struct s_philo
{
	int				time_to_die;
	int				time_to_eat;
	int				num_of_philo;
	int				time_to_sleep;
	int				h_m_must_eat;
	int				count_eat_each;
	int				n;
	int				death_flag;
	size_t			time_last_eat;
	size_t			start_time;
	pid_t			*pid;
	pthread_t		*t;
	t_sem			*sem;
}					t_philo;

unsigned int		ft_atoi(const char *str);
size_t				get_time(void);
void				upgrade_usleep(double msec);
int					init_struct(t_philo *ph, char **argv);
void				print_logs(char *str, t_philo *ph);
int					parse(t_philo *ph, char **argv);
void				my_free(t_philo *ph);
void				my_exit(char *error, t_philo *ph);
void				ft_sem_close(t_philo *ph);
void				*check_status(void *ptr);

#endif
