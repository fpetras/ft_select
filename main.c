/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 10:24:59 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/27 11:54:49 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Utilized termcaps:
**
** "cl" - to clear the screen
** "vi" - to make the cursor invisible
** "ve" - to make the cursor visible again
** "us" - to turn on 'underline mode'
** "mr" - to enter 'reverse video mode'
** "vb" - to cause the screen to flash
*/

static void	ft_select(void)
{
	char buf[4];

	while (42)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putc);
		ft_display();
		ft_bzero(buf, 3);
		read(0, buf, 3);
		buf[3] = '\0';
		ft_easteregg(buf);
		ft_arrows(buf);
		ft_spacebar(buf);
		ft_delete_backspace(buf);
		if (ft_enter(buf) == 0)
			break ;
		if (ft_escape(buf) == 0)
			break ;
		if (!ft_tablen(g_sel.args))
		{
			tputs(tgetstr("cl", NULL), 1, ft_putc);
			break ;
		}
	}
}

static char	**ft_copy_args(int ac, char **av)
{
	int		i;
	char	**args;

	i = 1;
	if (!(args = (char**)malloc(sizeof(char*) * ac)))
		return (NULL);
	while (av[i])
	{
		args[i - 1] = ft_strdup(av[i]);
		i++;
	}
	args[i - 1] = 0;
	return (args);
}

static int	ft_init_struct(int ac, char **av)
{
	int		i;
	char	*name;

	i = -1;
	if (!(g_sel.args = ft_copy_args(ac, av)))
		return (-1);
	if (!(g_sel.selected = (int*)malloc(sizeof(int) * (ac - 1))))
	{
		ft_free_tab(g_sel.args);
		return (-1);
	}
	while (++i < ac - 1)
		g_sel.selected[i] = UNSELECTED;
	g_sel.cursor = 0;
	g_sel.color = 0;
	if ((name = ttyname(0)))
		g_sel.fd = open(name, O_WRONLY | O_NOCTTY);
	else
		g_sel.fd = 0;
	return (0);
}

static int	ft_error(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		ft_dprintf(2, "usage: %s arg1 ...\n", av[0]);
		return (-1);
	}
	else if (!env[0] || !getenv("TERM") || !ft_strlen(getenv("TERM")))
	{
		ft_dprintf(2, "TERM environment variable not set.\n");
		return (-1);
	}
	else if (tgetent(NULL, getenv("TERM")) < 1)
	{
		ft_dprintf(2, "tgetent error\n");
		return (-1);
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	if (ft_error(ac, av, env) == -1)
		return (-1);
	if (ft_init_struct(ac, av) == -1)
		return (-1);
	ft_signals();
	ft_set_terminal();
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("vi", NULL), 1, ft_putc);
	ft_signal_func(SIGWINCH);
	ft_select();
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	ft_restore_terminal();
	ft_free_tab(g_sel.args);
	free(g_sel.selected);
	return (0);
}
