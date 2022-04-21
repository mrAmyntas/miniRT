/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 15:54:18 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/02/09 17:43:47 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buff;
	int		x;
	int		i;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	x = ft_strlen(s1) + ft_strlen(s2) + 1;
	buff = (char *)malloc(sizeof(char) * x);
	if (buff == NULL)
		ft_error(NULL, -1);
	x = 0;
	while (s1[x] != '\0')
	{
		buff[x] = s1[x];
		x++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		buff[x] = s2[i];
		i++;
		x++;
	}
	buff[x] = '\0';
	return (buff);
}
