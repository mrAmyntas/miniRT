/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atod.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgroen <mgroen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:37:15 by mgroen        #+#    #+#                 */
/*   Updated: 2022/06/29 17:57:36 by mgroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

int	num_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] > 47 && str[i] < 58)
		i++;
	return (i);
}

double	ft_atod(char *str)
{
	int		x;
	int		y;
	double	digit;
	char	**nums;

	nums = ft_split(str, '.');
	x = ft_atoi(nums[0]);
	if (!nums[1])
		y = 0;
	else
		y = ft_atoi(nums[1]);
	digit = y;
	if (nums[1])
		digit /= pow(10, num_strlen(nums[1]));
	if (x < 0)
		digit -= x;
	else
		digit += x;
	if (str[0] == '-')
		digit *= -1;
	free_strstr(nums);
	return (digit);
}
