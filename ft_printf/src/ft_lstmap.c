/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:30:07 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/09 14:18:44 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *first;
	t_list *tmp;

	if (!f)
		return (NULL);
	first = NULL;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp)
		{
			ft_lstadd_back(&first, tmp);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&first, del);
			break ;
		}
	}
	return (first);
}
