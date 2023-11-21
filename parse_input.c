/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/07/04 12:42:16 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	count_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->nbr_pipe = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '|')
			cmd->nbr_pipe++;
		i++;
	}
}

void	split_pipes(t_cmd *cmd)
{
	int		i;
	char	**split_pipes;

	i = 0;
	split_pipes = ft_split(cmd->cmd, '|');
	if (check_split(split_pipes, cmd) == 1)
	{
		free_s(split_pipes);
		printf("Syntax Error\n");
		return ;
	}
	cmd->box = malloc((sizeof(char **)) * (cmd->nbr_pipe + 2));
	while (split_pipes[i])
	{
		cmd->box[i] = ft_split(split_pipes[i], ' ');
		i++;
	}
	cmd->box[i] = NULL;
	i = 0;
	free_s(split_pipes);
}

void	add_spaces(t_cmd *cmd)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (cmd->box[i])
	{
		j = 0;
		while (cmd->box[i][j])
		{
			x = 0;
			while (cmd->box[i][j][x])
			{
				if (cmd->box[i][j][x] == 17)
					cmd->box[i][j][x] = ' ';
				if (cmd->box[i][j][x] == 18)
					cmd->box[i][j][x] = '|';
				x++;
			}
			j++;
		}
		i++;
	}
}

void	ft_parse_input1(t_cmd *cmd, char **envp)
{
	cmd->count++;
	convert(cmd);
	flag_init(cmd);
	count_pipes(cmd);
	check_heredoc(cmd);
	split_pipes(cmd);
	if (cmd->syntax_err == 1)
	{
		g_exitstatus = 127;
		return ;
	}
	cmd->output = NULL;
	cmd->input = NULL;
	add_spaces(cmd);
	look_var(cmd, envp);
	look_here_doc(cmd, 0, 0);
}

void	parse_input(t_cmd *cmd, char **envp)
{
	ft_parse_input1(cmd, envp);
	if (syntax_err(cmd) == 1)
		return ;
	if (cmd->box[0][0] == NULL)
		return ;
	if (ft_strcmp(cmd->box[0][0], "export") == 0)
		look_var_envp(cmd, envp);
	if (ft_strcmp(cmd->box[0][0], "unset") == 0)
		ft_unset(cmd->box[0], cmd);
	if (ft_strcmp(cmd->box[0][0], "cd") == 0)
	{
		ft_cd(cmd->box[0]);
		if (cmd->box[1] != NULL)
			cmd->box++;
	}
	if (ft_strcmp(cmd->box[0][0], "exit") == 0)
		ft_exit(cmd);
	if (g_exitstatus != 666)
	{
		execute_command(cmd, cmd->nbr_pipe, envp);
		free_in_out(cmd);
		unlink("heredoc_tmp.txt");
	}
	if (g_exitstatus == 666)
		g_exitstatus = 1;
}
