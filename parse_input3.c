/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/30 16:51:59 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_dquote(t_cmd *cmd)
{
	if (ft_chr(cmd->cmd, '"', cmd->ints->i + 1) == 0)
		cmd->dquote = 1;
	if (cmd->cmd[cmd->ints->i - 1] != '=' && cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->ints->j = cmd->ints->i -1;
	cmd->ints->i++;
	cmd->squote = 0;
	while (cmd->cmd[cmd->ints->i] != '"' && cmd->dquote == 1)
	{
		if (cmd->cmd[cmd->ints->i] == ' ')
			cmd->cmd[cmd->ints->i] = 17;
		if (cmd->cmd[cmd->ints->i] == '|')
			cmd->cmd[cmd->ints->i] = 18;
		if (cmd->cmd[cmd->ints->i] == 20)
			cmd->cmd[cmd->ints->i] = '$';
		cmd->ints->i++;
	}
	if (cmd->cmd[cmd->ints->j] != '=' && cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->dquote = 0;
}

void	handle_squote(t_cmd *cmd)
{
	if (ft_chr(cmd->cmd, '\'', cmd->ints->i + 1) == 0)
		cmd->squote = 1;
	if (cmd->cmd[cmd->ints->i - 1] != '=' && cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->ints->j = cmd->ints->i -1;
	cmd->ints->i++;
	cmd->dquote = 0;
	while (cmd->cmd[cmd->ints->i] != '\'' && cmd->squote == 1)
	{
		if (cmd->cmd[cmd->ints->i] == ' ')
			cmd->cmd[cmd->ints->i] = 17;
		if (cmd->cmd[cmd->ints->i] == '|')
			cmd->cmd[cmd->ints->i] = 18;
		if (cmd->cmd[cmd->ints->i] == '$')
			cmd->cmd[cmd->ints->i] = 20;
		cmd->ints->i++;
	}
	if (cmd->cmd[cmd->ints->j] != '=' && cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->squote = 0;
}

void	convert_dquote(t_cmd *cmd)
{
	cmd->ints = malloc(sizeof(t_int));
	cmd->ints->j = 0;
	cmd->ints->i = 0;
	{
		while (cmd->cmd[cmd->ints->i])
		{
			if (handle_halper(cmd) == 1)
				break ;
			cmd->ints->i++;
		}
	}
	free(cmd->ints);
}
