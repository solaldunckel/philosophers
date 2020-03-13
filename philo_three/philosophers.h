/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:42:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/13 15:20:06 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <signal.h>

# define S_WRITE "write"
# define S_FORK "fork"

typedef struct	s_philo
{
	int					pos;
	time_t				last_eat;
	int					eating;
	pthread_t			thr;
	pid_t				pid;
	struct s_options	*options;
}				t_philo;

typedef struct	s_options
{
	int					philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	int					dead;
	time_t				start_time;
	int					total_eat;
	sem_t				*write;
	sem_t				*forks;
	t_philo				*philos;
}				t_options;

void			philo_routine(t_philo *philo);
int				parse_params(t_options *options, char **argv);
int				create_philos(t_options *options);
int				create_fork(t_philo *philo);
void			monitor(t_options *options, int philo_num);
void			destroy_all(t_options *options);

/*
** PRINT_UTILS
*/

void			state_msg(t_philo *philo, char *str, time_t start_time);
void			state_msg2(t_philo *philo, char *str, time_t start_time);
int				ft_putstr(char *str);
/*
** UTILS
*/

time_t			get_time(void);
int				ft_strlen(char *str);
int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t size);

#endif
