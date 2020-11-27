/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:01:05 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/07 22:17:43 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int n;

	if (!lst)
		return (0);
	n = 1;
	while (lst->next)
	{
		lst->next = lst->next->next;
		n++;
	}
	return (n);
}
