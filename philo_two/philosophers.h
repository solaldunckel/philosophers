/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:42:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/04/12 19:22:40 by sdunckel         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define S_WRITE "/write"
# define S_FORK "/fork"
# define S_EAT "/eat"

typedef struct	s_philo
{
	int					pos;
	time_t				last_eat;
	int					finished;
	sem_t				*eating;
	pthread_t			thr;
	pthread_t			monitor;
	struct s_options	*options;
}				t_philo;

typedef struct	s_options
{
	int					philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	time_t				start_time;
	int					finish;
	int					total_eat;
	sem_t				*write;
	sem_t				*forks;
	t_philo				*philos;
}				t_options;

void			philo_routine(t_philo *philo);
int				parse_params(t_options *options, char **argv);
int				create_philos(t_options *options);
void			monitor(t_philo *philo);

/*
** PRINT_UTILS
*/

void			state_msg(t_philo *philo, char *str, time_t start_time);
void			state_msg2(t_philo *philo, char *str, time_t start_time);
int				ft_putstr(int fd, char *str);
int				wrong_args(char *str, char **argv);
void			add_str_to_buf(char buf[], char *str, int *count);
void			add_int_to_buf(char buf[], time_t num, int *count);
/*
** UTILS
*/

time_t			get_time(void);
int				ft_strlen(char *str);
int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t size);

#endif
