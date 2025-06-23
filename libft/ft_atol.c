/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:16 by qboutel           #+#    #+#             */
/*   Updated: 2025/01/27 17:43:10 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	ret;
	int		i;
	int		signe;

	i = 0;
	ret = 0;
	signe = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i ++;
	if (str[i] == '-')
	{
		signe *= -1;
		i ++;
	}
	else if (str[i] == '+')
		i ++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (ret * 10) + (str[i] - 48);
		i ++;
	}
	return (ret * signe);
}
