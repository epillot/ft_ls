/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:04:53 by epillot           #+#    #+#             */
/*   Updated: 2016/11/22 17:26:49 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*elem;

	if (*alst)
	{
		elem = *alst;
		(*del)(elem->content, elem->content_size);
		free(*alst);
		*alst = NULL;
	}
}
