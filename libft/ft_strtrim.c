/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bhoitzin <bhoitzin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 17:51:15 by bhoitzin      #+#    #+#                 */
/*   Updated: 2022/02/02 18:59:25 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkprefix(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0') && (j < ft_strlen(set)))
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				i++;
				break ;
			}
			j++;
		}
	}
	return (i);
}

static int	ft_checksuffix(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while ((s1[i] != '\0') && (j < ft_strlen(set)))
	{
		j = 0;
		while (set[j] != '\0')
		{
			if ((s1[i] == set[j]) && (i != 0))
			{
				i--;
				break ;
			}
			j++;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
	{
		ret = (char *)malloc(1);
		ret[0] = '\0';
		return (ret);
	}
	if (ft_strlen(set) == 0)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	i = ft_checkprefix(s1, set);
	j = ft_checksuffix(s1, set);
	if (i > j)
		return (ft_substr(s1, 0, 0));
	return (ft_substr(s1, i, (j - i + 1)));
}
