/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qboutel <qboutel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:29:40 by qboutel           #+#    #+#             */
/*   Updated: 2024/11/20 19:41:37 by qboutel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nl;

	nl = n;
	if (nl < 0)
	{
		ft_putchar('-', fd);
		nl = -nl;
	}
	if (nl >= 10)
		ft_putnbr_fd(nl / 10, fd);
	ft_putchar((nl % 10) + 48, fd);
}
