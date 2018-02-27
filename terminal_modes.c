/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_modes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 08:20:03 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/27 09:13:54 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_set_terminal(void)
{
	if (tcgetattr(0, &g_sel.old_config) < 0)
		ft_exit(1);
	if (tcgetattr(0, &g_sel.new_config) < 0)
		ft_exit(1);
	g_sel.new_config.c_lflag &= ~ECHO;
	g_sel.new_config.c_lflag &= ~ICANON;
	g_sel.new_config.c_cc[VMIN] = 1;
	g_sel.new_config.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &g_sel.new_config) < 0)
		ft_exit(1);
}

void	ft_restore_terminal(void)
{
	if (tcsetattr(0, TCSANOW, &g_sel.old_config) < 0)
		ft_exit(1);
}
