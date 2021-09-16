/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:04:15 by anhovhan          #+#    #+#             */
/*   Updated: 2021/08/31 18:04:20 by anhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void ft_pipein(char *cmd1, int fd[2], int in)
{
  char **args;

  close(fd[0]);
  args = ft_split(cmd1, ' ');
  dup2(fd[1], 1);
  dup2(in, 0);
  if (args[0][0] == '/')
  {
    if (execve(args[0], args, environ) == -1)
      ft_exit("Invalid command address", 2);
  }
  else
    ft_paths(args[0], args);
  ft_free(args);
  close(fd[1]);
  close(in);
}

void ft_pipeout(char *cmd2, int fd[2], int out)
{
  char **args;

  close(fd[1]);
  args = ft_split(cmd2, ' ');
  dup2(fd[0], 0);
  dup2(out, 1);
  if (args[0][0] == '/')
  {
    if (execve(args[0], args, environ) == -1)
      ft_exit("Invalid command address", 2);
  }
  else
    ft_paths(args[0], args);
  ft_free(args);
  close(fd[0]);
  close(out);
  wait(NULL);
}

void ft_paths(char *cmd, char **args)
{
  int i;
  char **paths;

  paths = NULL;
  i = 0;
  while (environ[i])
  {
    if (ft_strncmp(environ[i], "PATH", 4) == 0)
    {
      paths = ft_split((environ[i] + 5), ':');
      break;
    }
    i++;
  }
  ft_testpaths(cmd, args, paths);
}

void ft_testpaths(char *cmd, char **args, char **paths)
{
  int i;
  char *temp;
  char *newpath;

  i = 0;
  while (paths[i])
  {
    temp = ft_strjoin(paths[i], "/");
    newpath = ft_strjoin(temp, cmd);
    execve(newpath, args, environ);
    free(newpath);
    free(temp);
    i++;
  }
  ft_free(paths);
  perror("No such command found.");
  exit(2);
}
