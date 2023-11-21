/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/26 17:29:59 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*ft_sprint(const char	*str1, const char	*str2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = (char *)malloc((len1 + len2 + 2) * sizeof(char));
	ft_strcpy(result, str1);
	return (result);
}

void	set_upt(t_upt *upt, t_cmd *cmd)
{
	upt->name = NULL;
	upt->i = 0;
	upt->env_size = 0;
	upt->env = cmd->cpy_env;
	upt->new_env = NULL;
	upt->new_variable = NULL;
	while (upt->env[upt->env_size] != NULL)
		upt->env_size++;
}

void	update_environment(t_cmd *cmd, char *variable, char *value)
{
	t_upt	upt;

	set_upt(&upt, cmd);
	if (cmd == NULL || variable == NULL || value == NULL)
		return ;
	while (upt.i < upt.env_size)
	{
		upt.name = take_var(variable);
		if (ft_strncmp(upt.env[upt.i], upt.name, ft_strlen(upt.name)) == 0)
		{
			up_extra(&upt);
			upt.env[upt.i] = ft_sprint(variable, value);
			return ;
		}
		free(upt.name);
		upt.i++;
	}
	upt.new_env = realloc(upt.env, (upt.env_size + 2) * sizeof(char *));
	if (upt.new_env == NULL)
		return ;
	upt.new_variable = (char *)malloc((strlen(variable) + 1) * sizeof(char));
	ft_strcpy(upt.new_variable, variable);
	upt.new_env[upt.env_size] = upt.new_variable;
	upt.new_env[upt.env_size + 1] = NULL;
	cmd->cpy_env = upt.new_env;
}

void	look_var_envp(t_cmd *cmd, char **envp)
{
	int		i;
	int		j;
	char	*value;

	(void)envp;
	i = 0;
	j = 0;
	value = NULL;
	while (cmd->box[i])
	{
		j = 0;
		while (cmd->box[i][j])
		{
			if (check_var(cmd->box[i][j]) == 1)
			{
				value = getcnt(cmd->box[i][j], j, ft_strlen(cmd->box[i][j]));
				update_environment(cmd, cmd->box[i][j], value);
				free(value);
			}
			j++;
		}
		i++;
	}
}

void	look_var(t_cmd *cmd, char **envp)
{
	int		i;
	int		j;
	char	*value;

	(void)envp;
	i = 0;
	j = 0;
	value = NULL;
	while (cmd->box[i])
	{
		j = 0;
		while (cmd->box[i][j])
		{
			if (check_var(cmd->box[i][j]) == 1)
			{
				value = getcnt(cmd->box[i][j], j, ft_strlen(cmd->box[i][j]));
				update_environment(cmd, cmd->box[i][j], value);
				free(value);
			}
			j++;
		}
		i++;
	}
}
