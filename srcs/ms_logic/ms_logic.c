/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <fgrea@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 06:13:46 by fgrea             #+#    #+#             */
/*   Updated: 2022/11/05 06:14:49 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//GERER LES SIGNAUX DE RETOURS POUR LE $?

static void	ms_std_in_and_out(t_list *tokens, int fd[2], int *fd_sync)
{
	close(fd[0]);
	dup2(*fd_sync, 0);
	close(*fd_sync);
	if (tokens->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
}

static int	ms_fork(t_data *data, t_list *tkn, int fd_sync)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd))
		return (-1);
	pid = fork();
	if (pid < 0)
		ms_error();
	else if (pid == 0)
	{
		ms_std_in_and_out(tkn, fd, &fd_sync);
		ms_find_cmd(data, (t_token *)(tkn->content));
		exit (data->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ms_signal_handler(WTERMSIG(status));
	if (WTERMSIG(status) == SIGINT)
		data->exit_status = 130;
	else if (WTERMSIG(status) == SIGQUIT)
		data->exit_status = 131;
	data->exit_status = WEXITSTATUS(status);
	close(fd_sync);
	return (close(fd[1]) * 0 + fd[0]);
}

void	ms_logic(t_data *data)
{
	int		fd_sync;
	t_list	*tkn;

	fd_sync = dup(0);
	tkn = data->tokens;
	if (!data->pipe_count)
		return (ms_find_cmd(data, (t_token *)(tkn->content)));
	while (tkn)
	{
		fd_sync = ms_fork(data, tkn, fd_sync);
		if (fd_sync == -1)
			return ;
		tkn = tkn->next;
	}
	close(fd_sync);
}
