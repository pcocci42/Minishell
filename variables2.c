/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/26 16:08:24 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	new_cmd(t_cmd *cmd, int i)
{
	int	j;
	int	x;

	j = 0;
	while (cmd->new_cmd[j])
	{
		ft_strcpy(cmd->box[i][j], cmd->new_cmd[j]);
		j++;
	}
	x = j;
	while (cmd->box[i][j])
		j++;
	while (j > x)
	{
		free(cmd->box[i][j]);
		j--;
	}
	free(cmd->box[i][j]);
	cmd->box[i][j] = NULL;
	free_dpointer(cmd->new_cmd);
}

void	realloc_env(t_cmd *cmd, int i)
{
	char	**cpy;
	int		j;

	cpy = malloc((sizeof(char *)) * (i + 1));
	j = 0;
	while (cmd->cpy_env[j])
	{
		cpy[j] = malloc(sizeof(char) * (ft_strlen(cmd->cpy_env[j]) + 1));
		ft_strcpy(cpy[j], cmd->cpy_env[j]);
		j++;
	}
	free_envp(cmd);
	cpy[j] = NULL;
	copy_envp2(cmd, cpy, j);
	free_dpointer(cpy);
}

void	unset_update(t_cmd *cmd, int i)
{
	int		index;
	char	**tmp;

	index = 0;
	while (cmd->cpy_env[index])
		index++;
	tmp = malloc(((sizeof(char *)) * (index)));
	index = 0 ;
	while (index < i)
	{
		tmp[index] = ft_strdup(cmd->cpy_env[index]);
		index++;
	}
	while (cmd->cpy_env[i + 1])
	{
		tmp[i] = ft_strdup(cmd->cpy_env[i + 1]);
		i++;
	}
	tmp[i] = NULL;
	copy_envp(cmd, tmp);
	free_dpointer(tmp);
}

void	copy_envp2(t_cmd *cmd, char **envp, int j)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (j + 1));
	i = 0;
	while (i < j)
	{
		new_env[i] = malloc((sizeof(char)) * (ft_strlen(envp[i]) + 1));
		ft_strcpy(new_env[i], envp[i]);
		i++;
	}
	new_env[i] = NULL;
	cmd->cpy_env = new_env;
}

void	set_cpy(t_cpy *cpy, t_cmd *cmd)
{
	cpy->i = 0;
	cpy->env_size = 0;
	cpy->new_env_index = 0;
	cpy->env = cmd->cpy_env;
	cpy->new_env = NULL;
	cpy->var_copy = NULL;
	while (cpy->env[cpy->env_size] != NULL)
		cpy->env_size++;
}
