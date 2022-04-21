/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: milan <milan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 16:41:10 by milan         #+#    #+#                 */
/*   Updated: 2022/04/21 19:20:41 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (!s1 || !s2)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[l] != '\0')
	{
		new_str[i + l] = s2[l];
		l++;
	}
	new_str[i + l] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	sub_s = malloc(len + 1);
	if (!sub_s)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		sub_s[i] = s[i + start];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

char	*ft_strdup(const char *s1)
{
	char	*copy_s1;
	char	*cs1;
	char	*result;
	int		i;

	if (s1 == NULL)
		return (NULL);
	cs1 = (char *)s1;
	i = 0;
	while (s1[i] != '\0')
		i++;
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	copy_s1 = result;
	while (*cs1 != '\0')
	{
		*copy_s1 = *cs1;
		copy_s1++;
		cs1++;
	}
	*copy_s1 = '\0';
	return (result);
}

int	ft_stop_newline(const char *str)
{
	int	l;

	l = 0;
	while (str[l])
	{
		if (str[l] == '\n')
			return (l);
		l++;
	}
	return (-1);
}
