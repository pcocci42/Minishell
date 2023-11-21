/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dochelp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:11:50 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/30 18:18:37 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	out_heredoc_help(t_cmd *cmd, int i, int j)
{
	while (cmd->box[i][j])
	{
		if (ft_strcmp(cmd->box[i][j], ">>") == 0)
		{
			cmd->f->re_out = 1;
			cmd->f->append_out = 1;
			cmd->hd_i = 1;
			break ;
		}
		if (ft_strcmp(cmd->box[i][j], ">") == 0)
		{
			cmd->f->re_out = 1;
			cmd->hd_i = 1;
			break ;
		}
		j++;
	}
	if (cmd->hd_i == 1)
		alloc_out(cmd, i, j);
}

void	alloc_out(t_cmd *cmd, int i, int j)
{
	int	len;

	len = ft_strlen(cmd->box[i][j + 1]);
	free(cmd->output);
	cmd->output = malloc((sizeof(char)) * (len + 1));
	ft_strcpy(cmd->output, cmd->box[i][j + 1]);
}

int	in_fd(t_cmd *cmd, int j, int i)
{
	int	input_fd;

	out_heredoc_help(cmd, i, j);
	input_fd = 0;
	if (j == 0)
	{
		if (cmd->output != NULL && cmd->f->re_out == 1
			&& cmd->f->append_out == 0)
			input_fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->output != NULL && cmd->f->re_out == 1
			&& cmd->f->append_out == 1)
			input_fd = open(cmd->output, 01 | O_CREAT | O_APPEND, 0644);
		else
			input_fd = open("heredoc_tmp.txt", 01 | O_CREAT | O_TRUNC, 0644);
	}
	else
		input_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (input_fd);
}

void	write_line(int input_fd, char *line)
{
	write(input_fd, line, ft_strlen(line));
	write(input_fd, "\n", 1);
	free(line);
}
