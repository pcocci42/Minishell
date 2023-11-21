/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/30 11:00:36 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_env(t_cmd *cmd, char **parsed, char **envp)
{
	(void)envp;
	if (ft_strcmp(parsed[0], "env") == 0 && (parsed[1] == NULL
			|| cmd->f->re_out == 1))
	{
		print_envp2((char **)cmd->cpy_env);
		g_exitstatus = 0;
	}
	else if (ft_strcmp(parsed[0], "env") == 0 && parsed[1] != NULL)
		g_exitstatus = 130;
}

void	delete_content(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '=')
		i++;
	tmp = malloc((sizeof(char)) * (i + 2));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '=';
	tmp[i + 1] = 0;
	ft_strcpy(str, tmp);
}

void	unset_enviroment(char	*varname, char	**envp)
{
	int	index;
	int	i;

	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strncmp(envp[index], varname, ft_strlen(varname)) == 0
			&& envp[index][strlen(varname)] == '=')
		{
			i = index;
			if (envp[i + 1] != NULL)
				ft_strcpy(envp[i], envp[i + 1]);
			else
			{
				free(envp[i]);
				envp[i] = NULL;
			}
			break ;
		}
		index++;
	}
}

void	unset_variable(t_cmd *cmd, const char *variable)
{
	t_cpy	cpy;

	set_cpy(&cpy, cmd);
	cpy.env = cmd->cpy_env;
	if (cmd == NULL || cmd->cpy_env == NULL || variable == NULL)
		return ;
	cpy.new_env = (char **)malloc((cpy.env_size + 1) * sizeof(char *));
	while (cpy.i < cpy.env_size)
	{
		if (ft_strncmp(cpy.env[cpy.i], variable, ft_strlen(variable)) != 0)
		{
			cpy.var_copy = ft_strdup(cpy.env[cpy.i]);
			if (fail_ma_un(&cpy) == 1)
				return ;
			cpy.new_env[cpy.new_env_index] = cpy.var_copy;
			cpy.new_env_index++;
		}
		cpy.i++;
	}
	cpy.new_env[cpy.new_env_index] = NULL;
	free_cpy(&cpy);
	cmd->cpy_env = cpy.new_env;
}

void	ft_unset(char **parsed, t_cmd *cmd)
{
	int		j;

	j = 1;
	while (parsed[j])
	{
		unset_variable(cmd, parsed[j]);
		j++;
	}
}
