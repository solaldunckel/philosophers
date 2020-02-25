/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:48:41 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/25 18:22:22 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		ft_atoi(const char *nptr)
{
	int		atoi;
	int		negative;

	atoi = 0;
	negative = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negative = 1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		atoi = atoi * 10 + *nptr - 48;
		nptr++;
	}
	return (negative ? -atoi : atoi);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

void	*ft_calloc(size_t size)
{
	size_t	i;
	void	*mem;

	i = 0;
	if (!(mem = malloc(size)))
		return (NULL);
	memset(mem, 0, size);
	return (mem);
}
