/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:33:22 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/24 15:18:49 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_quit(void)
{
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	tcsetattr(0, TCSANOW, &g_sel.old_config);
	ft_free_tab(g_sel.args);
	free(g_sel.selected);
	exit(0);
}

void		ft_segfault(void)
{
	ft_dprintf(2, "You found a segfault. Good job!\n");
	exit(1);
}

/*
** TIOCSTI - Faking input
** Insert the given byte in the input queue.
** (Could've also inserted '' or 26 instead of c_cc[VSUSP])
*/

void		ft_suspend(void)
{
	char request[2];

	request[0] = g_sel.new_config.c_cc[VSUSP];
	request[1] = '\0';
	ioctl(0, TIOCSTI, request);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	tcsetattr(0, TCSANOW, &g_sel.old_config);
	signal(SIGTSTP, SIG_DFL);
}

void		ft_continue(void)
{
	signal(SIGTSTP, ft_signal_func);
	tcsetattr(0, TCSANOW, &g_sel.new_config);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("vi", NULL), 1, ft_putc);
	ft_display();
}

void		ft_resize(void)
{
	struct winsize sz;

	tputs(tgetstr("cl", NULL), 1, ft_putc);
	ioctl(0, TIOCGWINSZ, &sz);
	g_sel.rows = sz.ws_row;
	g_sel.cols = sz.ws_col;
	ft_display();
}
