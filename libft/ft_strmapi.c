/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 17:18:05 by basz          #+#    #+#                 */
/*   Updated: 2022/02/02 19:04:01 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*buff;
	int				i;
	unsigned int	n;

	if (s == NULL)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (buff == NULL)
		return (NULL);
	i = 0;
	n = i;
	while (s[i] != '\0')
	{
		buff[i] = f(n, s[i]);
		i++;
		n++;
	}
	buff[i] = '\0';
	return (buff);
}
