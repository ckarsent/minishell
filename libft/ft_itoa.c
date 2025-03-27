/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:45:09 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/22 18:56:37 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_lennbr(long int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_strrev(char *str)
{
	char	tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		i++;
	}
}

static char	*ft_mallocnbr(char *nbr, long int nl, int neg)
{
	int	l;

	l = 0;
	if (nl == 0)
		nbr[l++] = '0';
	else
	{
		while (nl != 0)
		{
			nbr[l++] = '0' + ft_abs(nl % 10);
			nl /= 10;
		}
		if (neg)
			nbr[l++] = '-';
	}
	nbr[l] = '\0';
	ft_strrev(nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	int			neg;
	long int	nl;

	neg = 0;
	nl = n;
	if (nl < 0)
	{
		neg = 1;
		nl = -nl;
	}
	nbr = (char *)malloc((ft_lennbr(nl) + 1 + neg) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	return (ft_mallocnbr(nbr, nl, neg));
}
