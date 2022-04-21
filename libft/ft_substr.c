/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 14:03:03 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/02/02 18:58:56 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buff;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		buff = (char *)malloc(1);
		buff[0] = '\0';
		return (buff);
	}
	buff = (char *)malloc(sizeof(char) * (len + 1));
	if (buff == NULL)
		return (NULL);
	while ((len > i) && (s[start] != '\0'))
	{
		buff[i] = s[start];
		i++;
		start++;
	}
	buff[i] = '\0';
	return (buff);
}
