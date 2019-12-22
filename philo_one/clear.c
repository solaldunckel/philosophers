/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:18:35 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/22 18:19:09 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_options *options)
{
	int		i;

	i = 0;
	while (i < options->num)
	{
		pthread_mutex_destroy(&options->sticks[i]);
		pthread_mutex_destroy(&options->philos[i].mutex);
		i++;
	}
	free(options->sticks);
	if (options->philos)
	 	free(options->philos);
	pthread_mutex_destroy(&options->write);
	pthread_mutex_destroy(&options->mutex);
}
