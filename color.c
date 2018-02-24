/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:22:00 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/24 14:27:25 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_color(int index)
{
	if ((index % 6) == 0)
		ft_dprintf(g_sel.fd, "\033[0;31m");
	else if ((index % 6) == 1)
		ft_dprintf(g_sel.fd, "\033[0;32m");
	else if ((index % 6) == 2)
		ft_dprintf(g_sel.fd, "\033[0;33m");
	else if ((index % 6) == 3)
		ft_dprintf(g_sel.fd, "\033[0;34m");
	else if ((index % 6) == 4)
		ft_dprintf(g_sel.fd, "\033[0;35m");
	else if ((index % 6) == 5)
		ft_dprintf(g_sel.fd, "\033[0;36m");
	else
		ft_dprintf(g_sel.fd, "\033[0m");
}

void	ft_easteregg(char *buf)
{
	if (ft_key(buf) == F2)
	{
		if (g_sel.color == 0)
			g_sel.color = 1;
		else
			g_sel.color = 0;
	}
}
