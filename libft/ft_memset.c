/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 17:50:19 by basz          #+#    #+#                 */
/*   Updated: 2020/11/14 15:18:30 by basz          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	int		i;

	str = s;
	i = 0;
	while (n > 0)
	{
		str[i] = c;
		n--;
		i++;
	}
	return (str);
}
