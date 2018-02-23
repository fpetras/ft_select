/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 10:24:59 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/23 12:18:12 by fpetras          ###   ########.fr       */
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
** "vb" - to cause the screen to flash (i.e. 'party mode')
*/

static void			ft_select(void)
{
	char buf[4];

	while (42)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putc);
		ft_display();
		buf[0] = '\0';
		buf[1] = '\0';
		buf[2] = '\0';
		read(0, buf, 3);
		buf[3] = '\0';
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

static char			**ft_copy_args(int ac, char **av)
{
	int		i;
	char	**args;

	i = 1;
	args = (char**)malloc(sizeof(char*) * ac);
	while (av[i])
	{
		args[i - 1] = ft_strdup(av[i]);
		i++;
	}
	args[i - 1] = 0;
	return (args);
}

static void			ft_init_struct(int ac, char **av)
{
	int i;

	i = -1;
	g_sel.args = ft_copy_args(ac, av);
	g_sel.selected = (int*)malloc(sizeof(int) * (ac - 1));
	while (++i < ac - 1)
		g_sel.selected[i] = UNSELECTED;
	g_sel.cursor = 0;
}

static int			ft_error(int ac, char **env)
{
	if (ac == 1)
	{
		ft_dprintf(2, "usage: ./ft_select arg1 ...\n");
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

int					main(int ac, char **av, char **env)
{
	if (ft_error(ac, env) == -1)
		return (-1);
	ft_init_struct(ac, av);
	signal(SIGINT, ft_signal_func);
	signal(SIGQUIT, ft_signal_func);
	signal(SIGSEGV, ft_signal_func);
	signal(SIGTSTP, ft_signal_func);
	signal(SIGCONT, ft_signal_func);
	signal(SIGWINCH, ft_signal_func);
	tcgetattr(0, &g_sel.old_config);
	tcgetattr(0, &g_sel.new_config);
	g_sel.new_config.c_lflag &= ~(ECHO);
	g_sel.new_config.c_lflag &= ~(ICANON);
//	g_sel.new_config.c_cc[VMIN] = 1;
//	g_sel.new_config.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &g_sel.new_config);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	tputs(tgetstr("vi", NULL), 1, ft_putc);
//	ft_signal_func(SIGWINCH);
	ft_select();
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	tcsetattr(0, TCSADRAIN, &g_sel.old_config);
	ft_free_tab(g_sel.args);
	free(g_sel.selected);
	return (0);
}
