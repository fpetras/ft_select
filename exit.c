/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 08:14:10 by fpetras           #+#    #+#             */
/*   Updated: 2018/04/25 10:10:21 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_exit(int status)
{
	ft_free_tab(g_sel.args);
	free(g_sel.selected);
	ft_printf(TEXT_RESET);
	exit(status);
}
