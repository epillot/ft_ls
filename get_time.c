/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:00:33 by epillot           #+#    #+#             */
/*   Updated: 2017/01/05 16:17:52 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_time(time_t mtime)
{
	time_t	actual_time;
	char	*s_time;
	char	*output;

	time(&actual_time);
	s_time = ctime(&mtime);
	if (!(output = ft_strsub(s_time, 4, 12)))
		return (NULL);
	if (actual_time - mtime >= 15811200)
		ft_strncpy(output + 7, s_time + 19, 5);
	return (output);
}
