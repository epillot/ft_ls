/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:22:33 by epillot           #+#    #+#             */
/*   Updated: 2017/01/20 18:25:24 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_usage(char c)
{
	ft_printf_fd(2, "ft_ls: illegal option -- %c\n", c);
	ft_printf_fd(2, "usage: ft_ls [-ARSUacdflprtu] [file ...]\n");
	exit(EXIT_FAILURE);
}

static void	set_option_time(char c, t_lsopt *opt)
{
	if (c == 'u')
	{
		opt->u = 1;
		opt->c = 0;
		opt->uu = 0;
	}
	else if (c == 'c')
	{
		opt->c = 1;
		opt->u = 0;
		opt->uu = 0;
	}
	else if (c == 'U')
	{
		opt->uu = 1;
		opt->u = 0;
		opt->c = 0;
	}
}

static void	set_option(char c, t_lsopt *opt)
{
	if (c == 'l')
		opt->l = 1;
	else if (c == 'R')
		opt->rec = 1;
	else if (c == 'a')
		opt->a = 1;
	else if (c == 'A')
		opt->aa = 1;
	else if (c == 'r')
		opt->r = 1;
	else if (c == 't')
		opt->t = 1;
	else if (c == 'd')
		opt->d = 1;
	else if (c == 'p')
		opt->p = 1;
	else if (c == 'S')
		opt->ss = 1;
	else if (c == 'f')
		opt->f = 1;
	else if (c == 'u' || c == 'c' || c == 'U')
		set_option_time(c, opt);
	else if (c != '1')
		ls_usage(c);
}

static void	adjust_option(t_lsopt *opt)
{
	if (opt->f)
	{
		opt->a = 1;
		opt->t = 0;
		opt->r = 0;
		opt->ss = 0;
	}
	if (opt->ss)
		opt->t = 0;
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
			set_option(av[i][j], opt);
			j++;
		}
		i++;
	}
	adjust_option(opt);
	return (i);
}
