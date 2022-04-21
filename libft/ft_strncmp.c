/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:10:28 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/02/02 19:03:26 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	protect_null(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	int				j;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (protect_null(s1, s2));
	while (n != 0)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
		{
			j = str1[i] - str2[i];
			return (j);
		}
		i++;
		n--;
	}
	return (0);
}
