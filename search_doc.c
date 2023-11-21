/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:18:27 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/26 16:05:23 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	scorri_cmd(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		cmd->cmd++;
		i++;
	}
}

int	search_helper(t_cmd *cmd, int i, int flag)
{
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<')
		{
			if (ft_chr(cmd->cmd, '<', i + 1) == 0)
			{
				flag = 1;
				return (flag);
			}
		}
		i++;
	}
	return (0);
}

void	search_here(t_cmd *cmd)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (cmd->cmd[i])
		i++;
	while (i >= 0)
	{
		if (ft_chr(cmd->cmd, '|', i) == 0)
		{
			j = i + 1;
			break ;
		}
		i--;
	}
	flag = search_helper(cmd, i, flag);
	if (flag == 1)
		scorri_cmd(cmd, j);
}

int	fail_ma_un(t_cpy *cpy)
{
	int	j;

	j = 0;
	if (cpy->var_copy == NULL)
	{
		printf("Failed to allocate memory.\n");
		while (j < cpy->new_env_index)
		{
			free(cpy->new_env[j]);
			j++;
		}
		free(cpy->new_env);
		return (1);
	}
	return (0);
}

void	free_cpy(t_cpy *cpy)
{
	cpy->i = 0;
	while (cpy->i < cpy->env_size)
	{
		free(cpy->env[cpy->i]);
		cpy->i++;
	}
	free(cpy->env);
}
