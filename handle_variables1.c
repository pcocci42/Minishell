/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/07/03 13:53:01 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_path(char *full_path, char *dir, const char *string, char *path)
{
	while (dir != NULL)
	{
		full_path = (char *) malloc(ft_strlen(dir) + ft_strlen(string) + 2);
		if (full_path != NULL)
		{
			dir = ft_strjoin(dir, "/");
			free(full_path);
			full_path = ft_strjoin(dir, string);
			if (access(full_path, X_OK) == 0)
			{
				free(path);
				free(full_path);
				free(dir);
				return (0);
			}
			free(dir);
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(dir);
	return (1);
}

int	process_path(t_path *path, const char *string)
{
	path->path = ft_strdup(path->path_env);
	if (path->path != NULL)
	{
		path->dir = strtok(path->path, ":");
		if (ft_path(path->full_path, path->dir, string, path->path) == 0)
		{
			free(path->path_env);
			return (0);
		}
		free(path->path);
	}
	return (1);
}

int	is_valid_command(const char *string, t_cmd *cmd)
{
	t_path	path;

	if (!string)
		return (1);
	if (check_var((char *)string) == 1)
		return (0);
	if (access(string, X_OK) == 0)
		return (0);
	set_tpath(&path, cmd);
	if (path.path_env != NULL)
	{
		if (!process_path(&path, string))
			return (0);
	}
	free(path.path_env);
	if (!path.dir)
		free(path.dir);
	return (1);
}

//int	is_valid_command(const char	*string, t_cmd *cmd)
//{
//	t_path	path;

//	if (!string)
//		return (1);
//	if (check_var((char *)string) == 1)
//		return (0);
//	if (access(string, X_OK) == 0)
//		return (0);
//	set_tpath(&path, cmd);
//	if (path.path_env != NULL)
//	{
//		path.path = ft_strdup(path.path_env);
//		if (path.path != NULL)
//		{
//			path.dir = strtok(path.path, ":");
//			if (ft_path(path.full_path, path.dir, string, path.path) == 0)
//			{
//				free(path.path_env);
//				return (0);
//			}
//			free(path.path);
//		}
//	}
//	free(path.path_env);
//	if (!path.dir)
//		free(path.dir);
//	return (1);
//}

int	failed_alloc(t_cmd *cmd, int i, int j)
{
	if (cmd->cpy_env[i] == NULL)
	{
		printf("Failed to allocate memory.\n");
		while (j <= i)
		{
			free(cmd->cpy_env[j]);
			j++;
		}
		free(cmd->cpy_env);
		return (1);
	}
	return (0);
}

void	copy_envp(t_cmd *cmd, char **envp)
{
	int		env_size;
	char	**env;
	int		var_len;
	int		i;

	env = envp;
	env_size = 0;
	i = 0;
	if (cmd == NULL || envp == NULL)
		return ;
	while (env[env_size] != NULL)
		env_size++;
	cmd->cpy_env = (char **)malloc((env_size + 1) * sizeof(char *));
	if (cmd->cpy_env == NULL)
		return ;
	while (i < env_size)
	{
		var_len = ft_strlen(env[i]) + 1;
		cmd->cpy_env[i] = (char *)malloc(var_len * sizeof(char));
		if (failed_alloc(cmd, i, 0) == 1)
			return ;
		ft_strncpy(cmd->cpy_env[i], env[i], var_len);
		i++;
	}
	cmd->cpy_env[env_size] = NULL;
}
