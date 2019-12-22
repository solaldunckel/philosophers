/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:39:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/21 15:58:16 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

typedef struct	s_philo
{
	int 				pos;
	int					left;
	int					right;
	time_t				time;
	int					eat_amount;
	pthread_mutex_t		sleep;
	struct	s_options	*options;
}				t_philo;

typedef struct	s_options
{
	int					num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	time_t				start;
	int					count;
	int					total;
	pthread_mutex_t		write;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*sticks;
	t_philo				*philos;
}				t_options;

size_t		ft_strlen(const char *s);
int			ft_atoi(const char *nptr);
void		ft_putnbr(int n);
void		ft_putstr(char *s);

// ACTIONS
void 		take_sticks(t_philo *philo);
void 		drop_sticks(t_philo *philo);
void 		start_eating(t_philo *philo);
void 		start_sleep(t_philo *philo);
// UTILS
time_t		get_time();
void 		state_msg(t_philo *philo, char *str);

#endif
