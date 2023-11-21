/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/07/04 12:40:29 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "unistd.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exitstatus = 0;
	}
	else
		g_exitstatus = 1;
}

void	ft_freedone(t_cmd *cmd)
{
	printf("exit\n");
	cmd->fine = 0;
	if (cmd->cpy_env)
		free_envp(cmd);
	free(cmd->f);
	free_box(cmd);
	ft_done(cmd);
}

void	ft_freeez(t_cmd *cmd, int flag)
{
	if (flag == 1)
		printf("numeric argument required\n");
	else
		printf("too many arguments\n");
	g_exitstatus = 666;
	free_box(cmd);
}

void	ft_exit(t_cmd *cmd)
{
	if (g_exitstatus != 139)
	{
		if (cmd->syntax_err == 1)
			g_exitstatus = 127;
		if (cmd->box[0][1] && !cmd->box[0][2])
		{
			if (ft_checkatoi(cmd->box[0][1]) == 1)
				ft_freeez(cmd, 1);
			else
			{
				g_exitstatus = atoi(cmd->box[0][1]);
				if (g_exitstatus > 255)
					g_exitstatus = (g_exitstatus % 256);
				ft_freedone(cmd);
			}
		}
		else if (cmd->box[0][1] != NULL && cmd->box[0][2] != NULL)
			ft_freeez(cmd, 0);
		else
			ft_freedone(cmd);
	}
}

void	ft_cd(char **parsed)
{
	if (parsed[1])
	{
		if (chdir(parsed[1]) == -1)
			perror("chdir");
	}
	else
		chdir("/");
}
