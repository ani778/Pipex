#ifndef FT_PIPEX_H
#define FT_PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"

extern char **environ;

void ft_pipein(char *cmd1, int fd[2], int in);
void ft_pipeout(char *cmd2, int fd[2], int out);
void ft_paths(char *cmd, char **args);
void ft_testpaths(char *cmd, char **args, char **paths);
void ft_exit(char *s, int status);

#endif