/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:52:52 by fpetras           #+#    #+#             */
/*   Updated: 2018/05/27 12:22:47 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_print_arg_multi_column(char *arg, int index)
{
	if (g_sel.cursor == index)
		tputs(tgetstr("us", NULL), 1, ft_putc);
	if (g_sel.selected[index] == SELECTED)
		tputs(tgetstr("mr", NULL), 1, ft_putc);
	ft_dprintf(g_sel.fd, "%s", arg);
	if (g_sel.color)
		ft_color(index);
	else
		ft_dprintf(g_sel.fd, "\033[0m");
}

/*
** Storing of the total length of arguments printed in the current line
** Checking if the next argument still fits in the current line
** If not, go the next line
*/

static void	ft_display_multi_column2(void)
{
	int i;
	int line;

	i = 1;
	line = (int)ft_strlen(g_sel.args[0]);
	ft_print_arg_multi_column(g_sel.args[0], 0);
	while (g_sel.args[i])
	{
		if (line + (int)ft_strlen(g_sel.args[i]) < g_sel.cols)
		{
			ft_dprintf(g_sel.fd, " ");
			ft_print_arg_multi_column(g_sel.args[i], i);
		}
		else
		{
			ft_dprintf(g_sel.fd, "\n");
			ft_print_arg_multi_column(g_sel.args[i], i);
			line = 0;
		}
		line += (int)ft_strlen(g_sel.args[i]);
		line++;
		i++;
	}
}

/*
** Calculation to verify that the window's size is large enough to fit all args
*/

void		ft_display_multi_column(void)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (g_sel.args[i])
	{
		len += (int)ft_strlen(g_sel.args[i]);
		len++;
		i++;
	}
	if (len > (g_sel.cols * g_sel.rows) * 0.87)
		ft_dprintf(g_sel.fd, "Window\nsize\nis\ntoo\nsmall\n🖼");
	else
		ft_display_multi_column2();
}
