/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:23 by pcocci            #+#    #+#             */
/*   Updated: 2023/07/03 14:53:51 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exitstatus;

void	take_input(t_cmd *cmd, char **envp)
{
	char	*tmp;

	cmd->shell_prompt = "@minishell:> \033[0;37m";
	tmp = ft_strjoin("\033[1;32m", getenv("LOGNAME"));
	cmd->shell_prompt = ft_strjoin(tmp, cmd->shell_prompt);
	free(tmp);
	cmd->cmd = readline(cmd->shell_prompt);
	if (cmd->cmd == NULL)
	{
		if (cmd->cpy_env)
			free_envp(cmd);
		free(cmd->f);
		ft_done(cmd);
	}
	if (cmd->cmd != NULL && ft_strlen(cmd->cmd) != 0
		&& (check_pipes(cmd) == 0))
	{
		add_history(cmd->cmd);
		parse_input(cmd, envp);
	}
	else if (ft_strlen(cmd->cmd) == 0)
		return ;
	free(cmd->shell_prompt);
}

void	loop(t_cmd *cmd, char **envp)
{
	while (1)
	{
		flag_init(cmd);
		take_input(cmd, envp);
		if (cmd->cmd != NULL && ft_strlen(cmd->cmd) != 0
			&& check_pipes(cmd) == 0 && cmd->syntax_err == 0
			&& cmd->box != NULL)
			free_box(cmd);
		else if (check_pipes(cmd) == 1 && ft_strlen(cmd->cmd) != 0)
			printf("Not a valid command\n");
		if (ft_strlen(cmd->cmd) == 0)
			free(cmd->shell_prompt);
		free(cmd->cmd);
		if (cmd->fine == 0)
			break ;
	}
}

void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig_num == SIGUSR1)
	{
		exit(0);
	}
	else
		return ;
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;

	(void) ac;
	(void) av;
	cmd.f = malloc(sizeof(t_flags));
	cmd.cpy_env = NULL;
	g_exitstatus = 0;
	cmd.fine = 1;
	copy_envp(&cmd, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	cmd.count = 0;
	loop(&cmd, envp);
	exit(g_exitstatus);
}
