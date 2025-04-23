/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:37:49 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/04/22 17:38:15 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	dup_fd(t_main *pipex, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error_exit(pipex, "Dup2 Error", errno);
}

void	create_own_pipes(t_main *pipex)
{
	if (pipe(pipex->fds[pipex->x]) == -1)
		error_exit(pipex, "Pipe Error", errno);
}

void	close_own_pipes(t_main *pipex)
{
	close(pipex->fds[pipex->x][0]);
	close(pipex->fds[pipex->x][1]);
}

void	close_last_pipes(t_main *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->args)
	{
		if (pipex->fds[pipex->x - 1][0] > 0)
			close(pipex->fds[pipex->x - 1][0]);
		if (pipex->fds[pipex->x - 1][1] > 0)
			close(pipex->fds[pipex->x - 1][1]);
		i++;
	}
}

void	wait_childrens(void)
{
	int	status;

	while (errno != ECHILD)
		waitpid(-1, &status, 0);
}
