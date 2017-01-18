/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 13:03:27 by epillot           #+#    #+#             */
/*   Updated: 2017/01/18 16:35:53 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_error(int errnum, char *str)
{
	if (errnum == 0)
	{
		if (*str)
			ft_printf_fd(2, "ls: %s: %s\n", str, strerror(errno));
		else
		{
			ft_printf_fd(2, "ls: %s: %s\n", "fts_open", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf_fd(2, "ls: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
