/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 07:56:55 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/27 11:54:56 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_signals(void)
{
	signal(SIGHUP, ft_signal_func);
	signal(SIGINT, ft_signal_func);
	signal(SIGQUIT, ft_signal_func);
	signal(SIGSEGV, ft_signal_func);
	signal(SIGTERM, ft_signal_func);
	signal(SIGTSTP, ft_signal_func);
	signal(SIGCONT, ft_signal_func);
	signal(SIGWINCH, ft_signal_func);
}
