/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:45:25 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/24 14:37:20 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	ft_max_arglen(void)
{
	int i;
	int max;

	i = 0;
	max = 0;
	while (g_sel.args[i])
	{
		if ((int)ft_strlen(g_sel.args[i]) > max)
			max = (int)ft_strlen(g_sel.args[i]);
		i++;
	}
	return (max);
}

static void	ft_print_arg_single_column(char *arg, int index)
{
	if (g_sel.cursor == index)
		tputs(tgetstr("us", NULL), 1, ft_putc);
	if (g_sel.selected[index] == SELECTED)
		tputs(tgetstr("mr", NULL), 1, ft_putc);
	ft_dprintf(g_sel.fd, "%s\n", arg);
	if (g_sel.color)
		ft_color(index);
	else
		ft_dprintf(g_sel.fd, "\033[0m");
}

/*
** Display all arguments in a single column if the window's height is sufficient
** Display only if the window's width is larger than any argument
*/

void		ft_display(void)
{
	int i;

	i = 0;
	if ((int)ft_tablen(g_sel.args) < g_sel.rows && ft_max_arglen() < g_sel.cols)
	{
		while (i < (int)ft_tablen(g_sel.args))
		{
			ft_print_arg_single_column(g_sel.args[i], i);
			i++;
		}
	}
	else if (ft_max_arglen() > g_sel.cols)
		ft_dprintf(g_sel.fd, "Window\nsize\nis\ntoo\nsmall\n🖼");
	else
		ft_display_multi_column();
}

void		ft_display_selection(void)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (g_sel.args[i])
	{
		if (g_sel.selected[i] == SELECTED)
			j = ft_dprintf(1, "%s", g_sel.args[i]);
		if (g_sel.args[i + 1] && g_sel.selected[i + 1] == SELECTED && j)
			ft_dprintf(1, " ");
		i++;
	}
}
