/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:19:13 by basz          #+#    #+#                 */
/*   Updated: 2022/02/02 19:00:06 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nee, size_t n)
{
	size_t	j;
	size_t	y;
	size_t	x;

	if (ft_strlen(nee) == 0)
		return ((char *)hay);
	j = 0;
	while ((hay[j] != '\0') && (j < n))
	{
		y = 0;
		x = ft_strlen(nee);
		if (x == 0)
			return ((char *)hay);
		while ((hay[j + y] == nee[y]) && (x > 0) && ((y + j) < n))
		{
			if (x == 1)
				return ((char *)&hay[j]);
			y++;
			x--;
		}
		j++;
	}
	return (NULL);
}
