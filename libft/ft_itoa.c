/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 19:27:16 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/02/09 17:34:04 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_reverse_buff(char *buff)
{
	int		i;
	int		j;
	char	str;

	i = 0;
	while (buff[i] != '\0')
		i++;
	i--;
	j = 0;
	if (buff[j] == '-')
		j++;
	while (i >= j)
	{
		str = buff[i];
		buff[i] = buff[j];
		buff[j] = str;
		i--;
		j++;
	}
	return (buff);
}

static char	*ft_allocmem(long int z, int n)
{
	char	*buff;

	if (n < 0)
		buff = (char *)malloc(sizeof(char) * (z + 2));
	else
		buff = (char *)malloc(sizeof(char) * (z + 1));
	return (buff);
}

static long int	ft_determine_len(long int str, long int y, long int z)
{
	while (str / y >= 1)
	{
		y = y * 10;
		z++;
	}
	return (z);
}

static char	*ft_fillbuff(int n, char *buff, long int z, long int str)
{
	int			i;
	long int	y;

	y = 10;
	i = 0;
	if (n < 0)
	{
		buff[i] = '-';
		i++;
		z++;
	}
	while (i < z)
	{
		buff[i] = (str % y / (y / 10) + 48);
		i++;
		y = y * 10;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_itoa(int n)
{
	char		*buff;
	long int	y;
	long int	z;
	long int	store;

	store = n;
	y = 10;
	z = 1;
	if (store < 0)
		store = store * -1;
	z = ft_determine_len(store, y, z);
	buff = ft_allocmem(z, n);
	if (buff == NULL)
		ft_error(NULL, -1);
	buff = ft_fillbuff(n, buff, z, store);
	buff = ft_reverse_buff(buff);
	return (buff);
}
