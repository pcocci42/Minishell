/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:06:14 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/30 15:50:26 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*expand_echo(char **parsed, int n)
{
	int	len;
	int	i;

	len = ft_strlen(parsed[n]);
	i = 0;
	while (i < len)
	{
		parsed[n][i] = parsed[n][i + 1];
		i++;
	}
	return (parsed[n]);
}

int	check_pipes(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->cmd[i] == '|')
		i++;
	while (cmd->cmd[i] <= 32 && cmd->cmd[i] != 0)
		i++;
	if (i == ft_strlen(cmd->cmd))
		return (1);
	return (0);
}

int	check_split(char **split_pipes, t_cmd *cmd)
{
	int	size;

	size = 0;
	if (!ft_strchr(cmd->cmd, '|'))
		return (0);
	while (split_pipes[size])
		size++;
	if (size > 1)
		size--;
	if (!split_pipes[size])
	{
		cmd->syntax_err = 1;
		return (1);
	}
	return (0);
}

void	free_s(char **split_pipes)
{
	int	i;

	i = 0;
	while (split_pipes[i])
	{
		free(split_pipes[i]);
		i++;
	}
	free(split_pipes[i]);
	free(split_pipes);
}

int	exe_helper(t_cmd *cmd, int i)
{
	if (is_valid_command(cmd->box[i][0], cmd) == 1
		&& check_cmds(cmd->box[i], 0) == 1)
	{
		write(2, "Syntax Error\n", 14);
		return (1);
	}
	return (0);
}
