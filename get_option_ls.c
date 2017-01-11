/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:22:33 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 14:54:26 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_option_ls(int ac, char **av, t_lsopt *opt)
{
	int		i;
	int		j;

	i = 1;
	ft_bzero(opt, sizeof(t_lsopt));
	while (i < ac && av[i][0] == '-' && av[i][1])
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'l')
				opt->l = 1;
			else if (av[i][j] == 'R')
				opt->rec = 1;
			else if (av[i][j] == 'a')
				opt->a = 1;
			else if (av[i][j] == 'r')
				opt->r = 1;
			else if (av[i][j] == 't')
				opt->t = 1;
			else
			{
				ft_printf("ft_ls: illegal option -- %c\n", av[i][j]);
				ft_printf("usage: ft_ls [-Ralrt] [file ...]\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (i);
}
