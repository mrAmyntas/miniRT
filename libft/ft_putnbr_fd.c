/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 20:41:54 by basz          #+#    #+#                 */
/*   Updated: 2022/02/02 19:06:15 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putstr(char *str, int fd)
{
	int	index;
	int	j;
	int	ret;

	j = 0;
	index = 11;
	while (str[j] == '0')
	{
		index--;
		j++;
	}
	ret = index;
	while (index != 0)
	{
		write(fd, &str[j], 1);
		index--;
		j++;
	}
	return (ret);
}

int	ft_putnbr_fd(int n, int fd)
{
	int		x;
	long	mod;
	long	nbb;
	char	str[12];
	int		i;

	nbb = n;
	mod = 10;
	i = 10;
	if (nbb == 0)
		write(fd, &"0", 1);
	if (nbb < 0)
	{
		write(fd, "-", 1);
		nbb = nbb * -1;
	}
	while (i >= 0)
	{
		x = nbb % mod / (mod / 10) + 48;
		str[i] = x;
		mod = mod * 10;
		i--;
	}
	x = ft_putstr(str, fd);
	return (x);
}
