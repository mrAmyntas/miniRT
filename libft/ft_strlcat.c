/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 18:38:46 by basz          #+#    #+#                 */
/*   Updated: 2022/02/02 19:04:35 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int					i;
	int					j;
	int					x;
	long unsigned int	y;

	i = 0;
	j = ft_strlen(dst);
	y = j;
	x = size - 1 - j;
	while ((src[i] != '\0') && (x > 0))
	{
		dst[j] = src[i];
		i++;
		j++;
		x--;
	}
	if (size >= y)
	{
		dst[j] = '\0';
		return (y + ft_strlen((char *)src));
	}
	return (size + ft_strlen((char *)src));
}
