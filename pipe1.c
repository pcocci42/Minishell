/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/30 16:56:58 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	expand_var(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->box[i])
	{
		j = 0;
		while (cmd->box[i][j])
		{
			if (cmd->box[i][j][0] == '$')
				cmd->box[i][j] = ft_getenv(cmd->box[i][j] + 1, cmd);
			j++;
		}
		i++;
	}
}

int	path_helper(char *path_env, char *path)
{
	if (path_env == NULL)
	{
		printf("Error: PATH environment variable not set.\n");
		return (1);
	}
	if (path == NULL)
	{
		perror("strdup");
		return (1);
	}
	return (0);
}

int	check_malloc(char *full_path, char *path)
{
	if (full_path == NULL)
	{
		perror("malloc");
		free(path);
		free(full_path);
		return (1);
	}
	return (0);
}

char	*fcp(const char *c, char *path, char *path_env, t_cmd *cmd)
{
	char	*full_path;
	char	*dir;

	path_env = ft_getenv("PATH", cmd);
	path = ft_strdup(path_env);
	dir = strtok(path, ":");
	if (path_helper(path_env, path) == 1)
		return (NULL);
	while (dir != NULL)
	{
		full_path = (char *)malloc (strlen(dir) + strlen(c) + 2);
		if (check_malloc(full_path, path) == 1)
			return (NULL);
		sprintf(full_path, "%s/%s", dir, c);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free_fcp(path, path_env);
	return (NULL);
}

int	count_redir(t_cmd *cmd, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	cmd->index.i_in = 0;
	cmd->index.i_out = 0;
	while (cmd->box[i][j])
	{
		if (ft_strcmp(cmd->box[i][j], "<") == 0
			|| ft_strcmp(cmd->box[i][j], "<<") == 0 ||
		ft_strcmp(cmd->box[i][j], ">>") == 0
			|| ft_strcmp(cmd->box[i][j], ">") == 0)
		{
			if (count == 0)
				cmd->index.i_in = j;
			else
				cmd->index.i_out = j;
			count++;
		}
		j++;
	}
	if (count == 0)
		flag_init(cmd);
	return (count);
}
