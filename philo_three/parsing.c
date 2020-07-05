/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:18:15 by sdunckel          #+#    #+#             */
/*   Updated: 2020/07/05 23:31:12 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		parse_params(t_options *options, char **argv)
{
	options->philo_num = ft_atoi(argv[1]);
	options->time_to_die = ft_atoi(argv[2]);
	options->time_to_eat = ft_atoi(argv[3]);
	options->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		options->max_eat = ft_atoi(argv[5]);
	else
		options->max_eat = 0;
	if (options->philo_num < 1 || options->time_to_die < 1
		|| options->max_eat < 0 || options->time_to_eat < 1
		|| options->time_to_sleep < 1)
		return (0);
	return (1);
}

int		wrong_args(char *str, char **argv)
{
	ft_putstr(2, "error: ");
	ft_putstr(2, str);
	ft_putstr(2, "\nusage: ");
	ft_putstr(2, argv[0]);
	ft_putstr(2, " number_of_philosophers time_to_die time_to_eat time_to_sleep"
		" [number_of_times_each_philosopher_must_eat]\n");
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
	char	name[1024];

	if (pos >= 0)
	{
		create_name(str, pos, name);
		str = name;
	}
	sem_unlink(str);
	sem = sem_open(str, O_CREAT, 0644, num);
	return (sem);
}

int		create_philos(t_options *options)
{
	int		i;

	i = -1;
	if (!(options->philos = ft_calloc(options->philo_num * sizeof(t_philo))))
		return (0);
	options->forks = create_sem(S_FORK, options->philo_num, -1);
	options->write = create_sem(S_WRITE, 1, -1);
	options->picking = create_sem(S_PICK, 1, -1);
	if (!options->forks || !options->write)
		return (0);
	while (++i < options->philo_num)
	{
		options->philos[i].eating = create_sem(S_EAT, 1, i);
		options->philos[i].pos = i;
		options->philos[i].options = options;
	}
	return (1);
}
