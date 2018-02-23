/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypresses.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:38:29 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/23 11:32:22 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_enter(char *buf)
{
	if (ft_key(buf) == ENTER)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putc);
		ft_display_selection();
		return (0);
	}
	return (1);
}

int		ft_escape(char *buf)
{
	if (ft_key(buf) == ESC)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putc);
		return (0);
	}
	return (1);
}

void	ft_spacebar(char *buf)
{
	if (ft_key(buf) == SPACEBAR)
	{
		if (g_sel.selected[g_sel.cursor] == UNSELECTED)
			g_sel.selected[g_sel.cursor] = SELECTED;
		else if (g_sel.selected[g_sel.cursor] == SELECTED)
			g_sel.selected[g_sel.cursor] = UNSELECTED;
		g_sel.cursor++;
		if (g_sel.cursor > (int)ft_tablen(g_sel.args) - 1)
		{
			tputs(tgetstr("vb", NULL), 1, ft_putc);
			g_sel.cursor = 0;
		}
		else if (g_sel.cursor < 0)
		{
			tputs(tgetstr("vb", NULL), 1, ft_putc);
			g_sel.cursor = (int)ft_tablen(g_sel.args) - 1;
		}
	}
}

void	ft_delete_backspace(char *buf)
{
	int i;
	int j;

	i = g_sel.cursor;
	j = g_sel.cursor;
	if (ft_key(buf) == DELETE || ft_key(buf) == BACKSPACE)
	{
		free(g_sel.args[i]);
		g_sel.args[i] = NULL;
		while (g_sel.args[i + 1])
		{
			g_sel.args[i] = ft_strdup(g_sel.args[i + 1]);
			free(g_sel.args[i + 1]);
			i++;
		}
		g_sel.args[i] = NULL;
		if (g_sel.cursor == (int)ft_tablen(g_sel.args) && ft_tablen(g_sel.args))
			g_sel.cursor--;
		while (g_sel.selected[j + 1])
		{
			g_sel.selected[j] = g_sel.selected[j + 1];
			j++;
		}
	}
}

void	ft_arrows(char *buf)
{
	if (ft_key(buf) == UP || ft_key(buf) == LEFT)
		g_sel.cursor--;
	else if (ft_key(buf) == DOWN || ft_key(buf) == RIGHT)
		g_sel.cursor++;
	if (g_sel.cursor > (int)ft_tablen(g_sel.args) - 1)
	{
		tputs(tgetstr("vb", NULL), 1, ft_putc);
		g_sel.cursor = 0;
	}
	else if (g_sel.cursor < 0)
	{
		tputs(tgetstr("vb", NULL), 1, ft_putc);
		g_sel.cursor = (int)ft_tablen(g_sel.args) - 1;
	}
}
