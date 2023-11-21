/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/07/03 15:26:58 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	checking_redir(t_cmd *cmd, int i)
{
	int	x;

	if (cmd->hd_i != 1)
	{
		{
			if (count_redir(cmd, i) <= 1)
			{
				x = is_there_more_commands(cmd, cmd->box[i]);
				if (x > 0 || !cmd->box[i + 1])
				{
					if (check_redirects_out(cmd, cmd->box[i], 0, 0) == 1)
						new_cmd(cmd, i);
					else
						free_dpointer(cmd->new_cmd);
				}
			}
			else
			{
				many_redir(cmd, i);
			}
		}
	}
}

void	open_pipes(int i, int num_pipes, int pipe_fds[num_pipes][2])
{
	while (i < num_pipes)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int i, int pipe_fds[i][2])
{
	if (i > 0)
	{
		close(pipe_fds[i - 1][0]);
		close(pipe_fds[i - 1][1]);
	}
}

void	inter_exe(t_cmd *cmd, char **envp, int i)
{
	char	*path;

	path = NULL;
	(void)envp;
	if (check_cmds(cmd->box[i], 0) == 1)
		path = fcp(cmd->box[i][0], 0, 0, cmd);
	if (check_cmds(cmd->box[i], 0) == 1 && check_var_loop(cmd->box[i]) == 0
		&& is_valid_command(cmd->box[i][0], cmd) == 0)
	{
		expand_var(cmd);
		if (ft_strchr(cmd->box[i][0], '/'))
			execve((cmd->box[i][0]), cmd->box[i], cmd->cpy_env);
		else
			execve(path, cmd->box[i], cmd->cpy_env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (check_cmds(cmd->box[i], 0) == 0
		|| check_var_loop(cmd->box[i]) == 1)
		custom_commands(cmd, i, envp);
	else
	{
		printf("%s: command not found\n", cmd->box[i][0]);
		exit(g_exitstatus);
	}
}

void	error_fork(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
