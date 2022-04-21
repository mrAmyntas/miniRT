/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:56:32 by bhoitzin      #+#    #+#                 */
/*   Updated: 2020/11/14 15:15:07 by basz          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	char	*s;
	size_t	i;

	s = str;
	i = 0;
	while (n > i)
	{
		s[i] = '\0';
		i++;
	}
}
