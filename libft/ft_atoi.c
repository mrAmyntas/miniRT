/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 13:31:11 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/02/02 18:58:28 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checklong(int j)
{
	if (j == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(char *str)
{
	long long unsigned int	i;
	int						j;
	long long unsigned int	n;

	i = 0;
	j = 1;
	n = 0;
	while (str[i] == '\v' || str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == ' ' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	if (n > LONG_MAX)
		return (ft_checklong(j));
	return (n * j);
}
