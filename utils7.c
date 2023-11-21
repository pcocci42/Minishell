/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/07/03 17:47:13 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	break_heredoc(t_cmd *cmd, int i, int j, int x)
{
	if (j == 0)
	{
		free_heredoc(cmd, i, j);
		return (1);
	}
	else
	{
		j = 1;
		l_heredoc_help(cmd, j, x, i);
		return (1);
	}
	return (0);
}

void	ft_realloc(char **env)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	copy = malloc((sizeof(char *)) * (i + 1));
	j = i + 1;
	i = 0;
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[j] = NULL;
}

void	ft_flag1(t_cmd *cmd, char *cmd2, char *cmd3)
{
	int	len;

	cmd2 += 2;
	cmd->nbr_pipe--;
	len = ft_strlen(cmd2);
	cmd3 = malloc((sizeof(char )) * (len + 1));
	ft_strcpy(cmd3, cmd2);
	free(cmd->cmd);
	cmd->cmd = cmd3;
}

void	check_heredoc(t_cmd *cmd)
{
	int		i;
	int		flag;
	char	*cmd2;
	char	*cmd3;
	int		len;

	i = 0;
	flag = 0;
	cmd2 = ft_strchr(cmd->cmd, '|');
	cmd3 = NULL;
	if (!cmd2)
		return ;
	len = ft_strlen(cmd2);
	while (i < len)
	{
		if (cmd2[i] == '<' && cmd2[i + 1] == '<')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1)
		ft_flag1(cmd, cmd2, cmd3);
}

int	syntax_err(t_cmd *cmd)
{
	if (cmd->syntax_err == 1)
	{
		cmd->syntax_err = 0;
		g_exitstatus = 127;
		return (1);
	}
	return (0);
}
