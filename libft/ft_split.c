/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 17:43:42 by basz          #+#    #+#                 */
/*   Updated: 2022/02/24 11:14:13 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freebuff(int j, char **buff)
{
	int	i;

	i = 0;
	while (j >= i)
	{
		free(buff[j]);
		buff[j] = NULL;
		j--;
	}
	free(buff);
	buff = NULL;
	ft_error(NULL, -1);
}

static int	ft_wordlength(int j, const char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	while (j >= 0)
	{
		while ((s[i] == c) && (s[i] != '\0'))
			i++;
		x = i;
		while ((s[i] != c) && (s[i] != '\0'))
			i++;
		j--;
	}
	return (i - x);
}

static int	ft_wordcount(char const *s, char c, int x)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			if (x >= 0)
			{
				if (x == 0)
					return (i);
			}
			i++;
		}
		x--;
		j++;
	}
	if (s[i - 1] == c)
		j--;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**buff;
	int		j;

	if (s == NULL)
		return (NULL);
	buff = (char **)malloc(sizeof(char *) * (1 + ft_wordcount(s, c, -1)));
	if (buff == NULL)
		ft_error(NULL, -1);
	j = 0;
	while (j < ft_wordcount(s, c, -1))
	{
		buff[j] = ft_substr(s, ft_wordcount(s, c, j), ft_wordlength(j, s, c));
		if (buff[j] == NULL)
			ft_freebuff(j, buff);
		j++;
	}
	buff[j] = NULL;
	return (buff);
}
