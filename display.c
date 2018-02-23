/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:45:25 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/23 11:16:19 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_color(char *arg)
{
	(void)arg;
	ft_dprintf(1, "\033[0m");
}

void		ft_display(void)
{
	int i;

	i = 0;
	while (i < (int)ft_tablen(g_sel.args))
	{
		if (g_sel.cursor == i)
			tputs(tgetstr("us", NULL), 1, ft_putc);
		if (g_sel.selected[i] == SELECTED)
			tputs(tgetstr("mr", NULL), 1, ft_putc);
		ft_dprintf(1, "%s\n", g_sel.args[i]);
		ft_color(g_sel.args[i]);
		i++;
	}
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
