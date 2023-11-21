/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/30 16:52:57 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*expand_echo2(char **parsed, int n)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = NULL;
	while (parsed[n][i + 1] != '\'')
		i++;
	new_var = malloc((sizeof(char)) * (i + 2));
	i = 0;
	while (parsed[n][i + 1] != '\'')
	{
		new_var[i] = parsed[n][i + 1];
		i++;
	}
	new_var[i] = '\0';
	free(parsed[n]);
	return (new_var);
}

void	handle_space_s(char **parsed, int n)
{
	if (parsed[n + 1][0] != '\'' && parsed[n + 1][0] != '"')
		write(1, " ", 1);
	else if (parsed[n + 1][0] == '\'' && ft_strlen(parsed[n + 1]) > 1)
		write(1, " ", 1);
	else if (parsed[n + 1][0] == '\'' && ft_strlen(parsed[n + 1]) == 1)
		parsed[n + 1][0] = 21;
}

void	handle_space_d(char **parsed, int n)
{
	if (parsed[n + 1][0] == '"' && ft_strlen(parsed[n + 1]) > 1)
		write(1, " ", 1);
	else if (parsed[n + 1][0] == '"' && ft_strlen(parsed[n + 1]) == 1)
	{
		parsed[n + 1][0] = 17;
	}
}

void	putstr_h(char *env, int i)
{
	if (env[i] == 21)
	{
		write(1, " ", 1);
		env[i] = '\'';
	}
	if (env[i] == 17)
	{
		write(1, " ", 1);
		env[i] = '"';
	}
}

char	*s_dollar(char *env, char **parsed, int n, t_cmd *cmd)
{
	char	*var;

	var = NULL;
	if (env[0] == '\'' && ft_strchr(env, '$'))
	{
		write(1, "\'", 1);
		env = expand_echo(parsed, n);
		env = expand_echo(parsed, n);
		var = ft_getenv(env, cmd);
		return (var);
	}
	return (NULL);
}
