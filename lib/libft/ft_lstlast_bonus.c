/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:29:01 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/23 19:06:31 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterate all the next pointer of the nodes until the last node is NULL
// lst is a pointer to the first node of the linked list
// The while loop checks for the content of the next pointer
// The tmp_lst is created to don't change the head of the linked list
// Returns the last node of the list.

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp_lst;

	if (!lst)
		return (NULL);
	tmp_lst = lst;
	while (tmp_lst->next != NULL)
	{
		tmp_lst = tmp_lst->next;
	}
	return (tmp_lst);
}
