/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:03:33 by fpetras           #+#    #+#             */
/*   Updated: 2018/02/27 08:23:51 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"

# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <signal.h>

# define UNSELECTED 1
# define SELECTED 2

# define ENTER 10
# define ESC 27
# define SPACEBAR 32
# define DELETE 126
# define BACKSPACE 127
# define UP 183
# define DOWN 184
# define RIGHT 185
# define LEFT 186
# define F2 187

typedef struct		s_select
{
	int				rows;
	int				cols;
	struct termios	old_config;
	struct termios	new_config;
	char			**args;
	int				*selected;
	int				cursor;
	int				color;
	int				fd;
}					t_select;

t_select			g_sel;

void				ft_set_terminal(void);
void				ft_restore_terminal(void);

void				ft_display(void);
void				ft_display_multi_column(void);
void				ft_display_selection(void);

int					ft_enter(char *buf);
int					ft_escape(char *buf);
void				ft_spacebar(char *buf);
void				ft_delete_backspace(char *buf);
void				ft_arrows(char *buf);

void				ft_easteregg(char *buf);
void				ft_color(int index);

int					ft_key(char *buf);
int					ft_putc(int c);
void				ft_signal_func(int sig);

void				ft_signals(void);
void				ft_quit(void);
void				ft_segfault(void);
void				ft_suspend(void);
void				ft_continue(void);
void				ft_resize(void);

size_t				ft_tablen(char **arr);
void				ft_free_tab(char **arr);
void				ft_exit(int status);

#endif
