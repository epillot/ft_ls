/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:20:28 by epillot           #+#    #+#             */
/*   Updated: 2017/01/25 15:17:49 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;

	i = 1;
	if (!n)
		return (0);
	while (i < n && *(t_byte*)s1 == *(t_byte*)s2)
	{
		s1++;
		s2++;
		i++;
	}
	return (*((t_byte*)s1) - *((t_byte*)s2));
}
