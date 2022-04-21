/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmapx.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: basz <basz@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:30:31 by basz          #+#    #+#                 */
/*   Updated: 2022/02/24 11:13:51 by bhoitzin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(void *ptr, void *ptr2)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	if (ptr2 != NULL)
	{
		free(ptr2);
		ptr2 = NULL;
	}
	return (NULL);
}

static	t_list	*ft_lstnewelem(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (ft_free(content, NULL));
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*ft_del)(void *))
{
	t_list	*newlist;
	t_list	*newlist2;
	t_list	*newlist3;

	if (lst == NULL)
		return (NULL);
	newlist = ft_lstnewelem(ft_strdup(lst->content));
	if (newlist == NULL)
		return (NULL);
	newlist = f(newlist->content);
	newlist2 = ft_lstnewelem(newlist);
	if (newlist2 == NULL)
		return (ft_free(newlist, NULL));
	newlist3 = newlist2;
	while (lst != NULL)
	{
		newlist = ft_lstnewelem(ft_strdup(lst->content));
		newlist2->next = ft_lstnewelem(newlist);
		if (newlist2->next == NULL)
			return (ft_free(newlist, newlist2));
		newlist2 = newlist2->next;
		lst = lst->next;
	}
	return (newlist3);
}
