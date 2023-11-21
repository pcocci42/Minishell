/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/07/04 11:36:54 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_nl(int tmp)
{
	if (tmp == 1)
		printf("\n");
}

void	ft_simple_echo(int n, t_cmd *cmd, char **parsed, int flag)
{
	cmd->tmp = n;
	cmd->f_echo = flag;
	if (check_echo(parsed, n) == 1)
		return ;
	while (parsed[n] != 0)
	{
		if (parsed[n][0] == '$' && parsed[n][1] != '?')
			ft_sticazzi(cmd, parsed, n);
		else if (parsed[n][0] == '\'' && parsed[n][1] == '$'
			&& ft_chr(parsed[n], '\'', 1) == 0)
			ft_sticazzi2(cmd, parsed, n);
		else if (ft_strchr(parsed[n], '$'))
			echo_dollar_plus(cmd, parsed, n);
		else
			echo_no_dollar(parsed, n, flag, cmd);
		if (parsed[n + 1])
			printf(" ");
		n++;
	}
	ft_nl(cmd->tmp);
	g_exitstatus = 0;
}

void	extra_echo(char **parsed, t_cmd *cmd)
{
	if (ft_strncmp(parsed[1], "$?", 2) == 0)
	{
		printf("%d\n", g_exitstatus);
		g_exitstatus = 0;
	}
	else
		ft_simple_echo(1, cmd, parsed, 0);
}

void	ft_echo(t_cmd *cmd, char **parsed, char **envp)
{
	(void)envp;
	if (ft_strncmp(parsed[0], "echo", 4) == 0)
	{
		if (parsed[1] == NULL)
			printf("\n");
		else if (ft_strcmp(parsed[1], "$") == 0 && !parsed[2])
			printf("$\n");
		else if (ft_strncmp(parsed[1], "-n", 2) == 0)
		{
			if (parsed[2])
			{
				if (ft_strncmp(parsed[2], "$?", 2) == 0)
				{
					printf("%d\n", g_exitstatus);
					g_exitstatus = 0;
				}
				else
					ft_simple_echo(2, cmd, parsed, 0);
			}
		}
		else
			extra_echo(parsed, cmd);
	}
}

void	custom_commands(t_cmd *cmd, int i, char **envp)
{
	char	**parsed;

	parsed = cmd->box[i];
	if (ft_strncmp(parsed[0], "pwd", 3) == 0)
		ft_pwd();
	ft_echo(cmd, parsed, envp);
	ft_export(cmd, parsed, envp);
	ft_env(cmd, parsed, envp);
	free_box(cmd);
	free(cmd->shell_prompt);
	free(cmd->f);
	free_dpointer(cmd->cpy_env);
	free_in_out(cmd);
	exit(g_exitstatus);
}
