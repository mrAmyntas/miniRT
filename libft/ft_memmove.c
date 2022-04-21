/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 10:43:47 by basz          #+#    #+#                 */
/*   Updated: 2022/02/02 19:06:34 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tempdst;
	size_t	i;

	tempdst = (char *)dest;
	i = 0;
	if ((tempdst == NULL) && ((char *)src == NULL))
		return (NULL);
	if (tempdst <= (char *)src)
	{
		while (n > i)
		{
			tempdst[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = i + n;
		while (i > 0)
		{
			tempdst[i - 1] = ((char *)src)[i - 1];
			i--;
		}
	}
	return (tempdst);
}
