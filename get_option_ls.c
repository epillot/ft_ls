/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:22:33 by epillot           #+#    #+#             */
/*   Updated: 2017/01/18 15:09:04 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_usage(char c)
{
	ft_printf_fd(2, "ft_ls: illegal option -- %c\n", c);
	ft_printf_fd(2, "usage: ft_ls [-Ralrt] [file ...]\n");
	exit(EXIT_FAILURE);
}

static void	get_option_ls_aux(char c, t_lsopt *opt)
{
	if (c == 'l')
		opt->l = 1;
	else if (c == 'R')
		opt->rec = 1;
	else if (c == 'a')
		opt->a = 1;
	else if (c == 'r')
		opt->r = 1;
	else if (c == 't')
		opt->t = 1;
	else if (c != '1')
		ls_usage(c);
}

int			get_option_ls(int ac, char **av, t_lsopt *opt)
{
	int		i;
	int		j;

	i = 1;
	ft_bzero(opt, sizeof(t_lsopt));
	while (i < ac && av[i][0] == '-' && av[i][1])
	{
		j = 1;
		if (av[i][1] == '-' && !av[i][2])
			return (i + 1);
		while (av[i][j])
		{
			get_option_ls_aux(av[i][j], opt);
			j++;
		}
		i++;
	}
	return (i);
}
