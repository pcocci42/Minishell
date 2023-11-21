/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/30 18:22:54 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	stampa(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == 20)
			env[i] = '$';
		if (env[i] == 18)
			env[i] = '|';
		putstr_h(env, i);
		write(1, &env[i], 1);
		i++;
	}
}

int	handle_halper(t_cmd *cmd)
{
	if (cmd->cmd[cmd->ints->i] == '"' && cmd->squote == 0)
	{
		if (cmd->ints->i - 1 > 0)
		{
			handle_dquote(cmd);
			if (!cmd->cmd[cmd->ints->i])
				return (1);
		}
	}
	else if (cmd->cmd[cmd->ints->i] == '\'' && cmd->dquote == 0)
	{
		if (cmd->ints->i - 1 > 0)
		{
			handle_squote(cmd);
			if (!cmd->cmd[cmd->ints->i])
				return (1);
		}
	}
	return (0);
}

void	free_fcp(char *path, char *path_env)
{
	free(path);
	free(path_env);
}

void	set_tpath(t_path *path, t_cmd *cmd)
{
	path->full_path = NULL;
	path->dir = NULL;
	path->path_env = ft_getenv("PATH", cmd);
	if (path->path_env == NULL)
		free(path->path_env);
}

void	free_heredoc(t_cmd *cmd, int i, int j)
{
	while (cmd->box[i][j])
	{
		free(cmd->box[i][j]);
		cmd->box[i][j] = NULL;
		j++;
	}
	free(cmd->output);
}
