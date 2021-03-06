/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:11:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/06 18:30:17 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define PARSE_ERROR 0

# define TAKEN_FORK "has taken a fork"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define EATING "is eating"
# define DEAD "died"

typedef struct	s_philo
{
	int					num;
	int					finished;
	time_t				last_eat;
	pthread_mutex_t		eating;
	pthread_t			thr;
	pthread_t			monitor;
}				t_philo;

typedef struct	s_options
{
	int					total_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	time_t				start_time;
	int					total_eat;
	int					finish;
	pthread_mutex_t		picking;
	pthread_mutex_t		write;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}				t_options;

t_options		*g_options;

int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t size);
void			ft_sleep(int n);
time_t			get_time(void);
int				ft_putstr_fd(int fd, char *str);

void			state_msg(t_philo *philo, char *str);
void			routine(t_philo *philo);

int				init_philos(t_options *opt);
int				init_params(char **argv, int argc, t_options *opt);

#endif
