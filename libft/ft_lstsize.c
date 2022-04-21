/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 20:35:13 by basz          #+#    #+#                 */
/*   Updated: 2020/11/15 20:39:45 by basz          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = lst;
	if (lst == NULL)
		return (0);
	if (lst->content != NULL)
		i++;
	while (temp->next != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
