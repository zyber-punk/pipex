/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:39:45 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/04/22 17:39:48 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_all_exit(t_main *pipex)
{
	free_all(pipex);
	exit(pipex->err);
}

void	error_exit(t_main *pipex, char *msg, int error)
{
	free_all(pipex);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(error);
}

void	malloc_error(t_main *pipex)
{
	free_all(pipex);
	ft_putendl_fd("Malloc Error", 2);
	exit(0);
}

void	free_all(t_main *pipex)
{
	int	i;

	i = 0;
	if (pipex)
	{
		if (pipex->cmd_paths)
			ft_free_double_tab(&pipex->cmd_paths);
		if (pipex->cmd_args)
		{
			while (pipex->cmd_args[i])
				ft_free_double_tab(&pipex->cmd_args[i++]);
			free(pipex->cmd_args);
		}
		if (pipex->paths)
			ft_free_double_tab(&pipex->paths);
		if (pipex->fds)
		{
			i = 0;
			while (i < pipex->args)
				free(pipex->fds[i++]);
			free(pipex->fds);
		}
		if (pipex->pids)
			free(pipex->pids);
	}
}
