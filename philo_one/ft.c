/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 02:26:59 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/21 03:09:35 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + 48);
	}
	if (nb < 10)
		ft_putchar(nb + 48);
}
