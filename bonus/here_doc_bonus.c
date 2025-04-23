/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:55:00 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/04/22 17:55:24 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	here_doc(t_main *pipex, char **envp, char **argv)
{
	malloc_fds(pipex);
	malloc_pids(pipex);
	pipex->x = 0;
	doc_pipe(pipex, argv);
	first_cmd(pipex, envp, argv);
	if (pipex->filein != -1)
		close(pipex->filein);
	pipex->x++;
	while (pipex->x < pipex->argc - 5)
		(mid_cmd(pipex, envp), pipex->x++);
	last_cmd(pipex, envp, argv);
	wait_childrens();
	if (pipex->filein)
		close(pipex->filein);
	close_last_pipes(pipex);
	close_own_pipes(pipex);
}

void	doc_pipe(t_main *pipex, char **argv)
{
	char	*line;
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit(pipex, "Pipe Error", errno);
	pid = fork();
	if (pid == -1)
		error_exit(pipex, "Fork Error", errno);
	if (pid == 0)
	{
		(close(fd[0]), ft_printf("pipe heredoc> "), line = get_next_line(0));
		while (line)
		{
			if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
				break ;
			(ft_printf("pipe heredoc> "), ft_putstr_fd(line, fd[1]));
			(free(line), line = NULL, line = get_next_line(0));
		}
		if (line)
			free(line);
		(free_all(pipex), close(fd[0]), close(fd[1]), exit(0));
	}
	else
		(waitpid(pid, NULL, 0), close(fd[1]), pipex->filein = fd[0]);
}
