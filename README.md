# ft_select

A terminal program with a simple user interface, built using the termcap library.\
Allows picking of elements from a list and returning them to the shell.

## Installation:

`git clone --recurse-submodules https://github.com/fpetras/ft_select.git && cd ft_select && make`

## Usage:

`usage: ./ft_select arg1 ...`

- **Arrow keys:** Move cursor through the list of arguments
- **Delete/Backspace:** Erase the element under the cursor from the list
- **Spacebar:** Select or unselect choices
- **Enter/Return:** Validate the selection. The program will exit and the choices will be sent to the shell
- **Esc:** Exit the program without sending anything to the shell
- **F2:** Enable colors

The elements will automatically reposition themselves upon resizing of the window.

Command substitution allows acting upon the list of choices:

`` ls -l `./ft_select *` ``: Display information about the selected files\
`` cat `./ft_select *` ``: Display the contents of the selected files\
`` less `./ft_select *` ``: Browse through the contents of the selected files\
`` rm -rf `./ft_select *` ``: Remove the selected files\
`` for dir in `./ft_select *` ; git -C $dir pull``: Update the selected Git repositories\
**...**

### In action:

![GIF1](http://g.recordit.co/o5MLualTzt.gif)

## Code snippet:

Initialization of the terminal:

```C
void    ft_set_terminal(void)
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
```

Deletion of elements from the list:

```C
void    ft_delete_backspace(char *buf)
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
```

## [Subject](https://github.com/fpetras/42-subjects/blob/master/ft_select.en.pdf "ft_select.en.pdf")
