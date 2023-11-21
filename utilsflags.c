/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:27:05 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/30 10:58:19 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	flag_init(t_cmd *cmd)
{
	cmd->f->append_out = 0;
	cmd->f->d_quote = 0;
	cmd->f->pipe = 0;
	cmd->f->quote = 0;
	cmd->f->re_in = 0;
	cmd->f->re_out = 0;
	cmd->f->write_in = 0;
	cmd->syntax_err = 0;
	cmd->hd_j = 0;
	cmd->hd_i = 0;
	cmd->custom = 0;
}

void	free_box(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->box[i])
	{
		j = 0;
		while (cmd->box[i][j])
		{
			free(cmd->box[i][j]);
			j++;
		}
		free(cmd->box[i]);
		i++;
	}
	free(cmd->box);
	cmd->box = NULL;
}

void	free_altro(t_cmd *cmd)
{
	free_box(cmd);
}

void	free_dpointer(char **dpoint)
{
	int	i;

	i = 0;
	if (!dpoint)
		return ;
	while (dpoint[i])
	{
		free(dpoint[i]);
		i++;
	}
	free(dpoint[i]);
	free(dpoint);
}

void	free_envp(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cpy_env[i])
	{
		free(cmd->cpy_env[i]);
		i++;
	}
	free(cmd->cpy_env);
	cmd->cpy_env = NULL;
}
