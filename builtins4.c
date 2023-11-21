/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/30 16:46:44 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*ft_putstr_quota(char *parsed)
{
	int		i;
	char	*var;

	var = malloc((sizeof(char)) * ft_strlen(parsed));
	i = 0;
	while (parsed[i] && parsed[i] != '\'')
	{
		if (parsed[i] == 18)
			parsed[i] = '|';
		var[i] = parsed[i];
		i++;
	}
	var[i] = 0;
	ft_strcpy(parsed, var);
	free(var);
	return (parsed);
}

void	echo_dollar(char **parsed, int n, t_cmd *cmd, int squote)
{
	char	*env;
	char	*var;

	env = NULL;
	var = NULL;
	if (cmd->cpy_env)
		env = ft_getenv(parsed[n], cmd);
	if (ft_strncmp(parsed[n], "-n", 2) != 0 || cmd->f_echo == 1)
	{
		if (squote == 0)
		{
			if (env != NULL)
				ft_putstr(env, parsed, n, cmd);
		}
		else
		{
			parsed[n] = expand_echo2(parsed, n);
			var = ft_getenv(parsed[n], cmd);
			printf("\'%s\'", var);
			free(var);
		}
		cmd->f_echo = 1;
	}
	free(env);
}

void	ft_putstr(char *env, char **parsed, int n, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	if (env[0] == '\'' && ft_strchr(env, '$'))
	{
		printf("open quote");
		return ;
	}
	stampa(env);
	if (parsed[n + 1])
	{
		handle_space_s(parsed, n);
		handle_space_d(parsed, n);
	}
}

void	echo_no_dollar(char **parsed, int n, int flag, t_cmd *cmd)
{
	if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
	{
		ft_putstr(parsed[n], parsed, n, cmd);
		flag = 1;
		if (parsed[n + 1] != 0)
			printf(" ");
	}
}

int	check_echo(char **parsed, int n)
{
	if (!parsed && n == 1)
	{
		g_exitstatus = 1;
		return (1);
	}
	return (0);
}
