/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:21:04 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/07 04:02:49 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		only_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int		init_params(char **argv, int argc, t_options *opt)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!only_digit(argv[i]))
			return (PARSE_ERROR);
		i++;
	}
	if ((opt->total_philo = ft_atoi(argv[1])) < 1)
		return (PARSE_ERROR);
	if ((opt->time_to_die = ft_atoi(argv[2])) < 1)
		return (PARSE_ERROR);
	if ((opt->time_to_eat = ft_atoi(argv[3])) < 1)
		return (PARSE_ERROR);
	if ((opt->time_to_sleep = ft_atoi(argv[4])) < 1)
		return (PARSE_ERROR);
	if (argv[5])
		if ((opt->max_eat = ft_atoi(argv[5])) < 1)
			return (PARSE_ERROR);
	return (1);
}

void	create_name(char *str, int pos, char name[])
{
	int		i;

	i = 0;
	add_str_to_buf(name, str, &i);
	name[i++] = '_';
	add_int_to_buf(name, (time_t)pos, &i);
	name[i] = '\0';
}

sem_t	*create_sem(char *str, int num, int pos)
{
	sem_t	*sem;
	char	name[32];

	if (pos >= 0)
	{
		create_name(str, pos, name);
		str = name;
	}
	sem_unlink(str);
	sem = sem_open(str, O_CREAT, 0644, num);
	return (sem);
}

int		init_philos(t_options *opt)
{
	int		i;

	i = 0;
	if (!(opt->philos = ft_calloc(sizeof(t_philo) * opt->total_philo)))
		return (0);
	opt->forks = create_sem(S_FORK, opt->total_philo, -1);
	opt->write = create_sem(S_WRITE, 1, -1);
	opt->picking = create_sem(S_PICK, 1, -1);
	while (i < opt->total_philo)
	{
		opt->philos[i].eating = create_sem(S_EAT, 1, i);
		opt->philos[i].num = i;
		i++;
	}
	return (1);
}
