/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:02:21 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/27 08:01:54 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_key(char *buf)
{
	int i;
	int key;

	i = 0;
	key = 0;
	while (buf[i])
	{
		key += buf[i];
		i++;
	}
	return (key);
}

int			ft_putc(int c)
{
	return (write(g_sel.fd, &c, 1));
}

void		ft_signal_func(int sig)
{
	if (sig == SIGHUP)
		ft_quit();
	else if (sig == SIGINT)
		ft_quit();
	else if (sig == SIGQUIT)
		ft_quit();
	else if (sig == SIGSEGV)
		ft_segfault();
	else if (sig == SIGTERM)
		ft_quit();
	else if (sig == SIGTSTP)
		ft_suspend();
	else if (sig == SIGCONT)
		ft_continue();
	else if (sig == SIGWINCH)
		ft_resize();
}
