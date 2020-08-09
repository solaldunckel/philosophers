/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:11:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/08 16:02:37 by sdunckel         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define S_WRITE "/write"
# define S_PICK "/pick"
# define S_FORK "/fork"
# define S_EAT "/eat"

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
	sem_t				*eating;
	pid_t				pid;
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
	sem_t				*picking;
	sem_t				*write;
	sem_t				*forks;
	t_philo				*philos;
}				t_options;

t_options		*g_options;

int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t size);
void			ft_sleep(int n);
time_t			get_time(void);
int				ft_putstr_fd(int fd, char *str);

void			state_msg(t_philo *philo, char *str);
void			state_msg2(t_philo *philo, char *str);
void			routine(t_philo *philo);
void			monitor(t_philo *philo);

int				init_philos(t_options *opt);
int				init_params(char **argv, int argc, t_options *opt);
sem_t			*create_sem(char *str, int num, int pos);
void			add_str_to_buf(char buf[], char *str, int *count);
void			add_int_to_buf(char buf[], time_t num, int *count);

#endif
