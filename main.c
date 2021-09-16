/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:04:52 by anhovhan          #+#    #+#             */
/*   Updated: 2021/09/16 18:05:02 by anhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void ft_exit(char *s, int status)
{
  perror(s);
  exit(status);
}
int main(int argc, char *argv[])
{
  int fd[2];
  int in;
  int out;
  int pid;

  in = open(argv[1], O_RDONLY);
  out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (in == -1)
    ft_exit("Failed to open input file.", 2);
  if (out == -1)
    ft_exit("Failed to open output file.", 2);

  if (pipe(fd) == -1)
    ft_exit("Failed to create a pipe.", 2);

  pid = fork();
  if (pid == -1)
    ft_exit("Failed to fork the process.", 2);

  if (pid == 0)
    ft_pipein(argv[3], fd, in);
  else
    ft_pipeout(argv[2], fd, out);

  return 0;
}

