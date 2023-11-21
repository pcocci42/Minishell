/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/07/04 11:54:46 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_jx(int j, int x, char *parsed)
{
	while (parsed[x] > 32 && parsed[x] != '\0'
		&& parsed[x] != '$' && parsed[x] != '\'')
	{
		j++;
		x++;
	}
	return (j);
}

int	ret_i(t_cmd *cmd, char *parsed, int i, int x)
{
	int		j;
	char	*cnt;
	char	*var;

	j = ft_jx(0, x, parsed);
	var = malloc((sizeof(char)) * (j + 1));
	x = i;
	j = 0;
	while (parsed[x] > 32 && parsed[x] != '\0'
		&& parsed[x] != '$' && parsed[x] != '\'')
	{
		var[j] = parsed[x];
		j++;
		x++;
	}
	var[j] = '\0';
	cnt = ft_getenv(var, cmd);
	free(var);
	if (cnt)
		ft_putstr_fd(cnt, 1);
	free(cnt);
	i = i + j;
	return (i);
}

void	echo_dollar_plus(t_cmd *cmd, char **parsed, int n)
{
	int		i;
	int		x;
	char	*var;

	var = NULL;
	i = 0;
	x = 0;
	while (parsed[n][i])
	{
		while (parsed[n][i] == '$')
		{
			i++;
			x = i;
			i = ret_i(cmd, parsed[n], i, x);
		}
		if (parsed[n][i])
		{
			write(1, &parsed[n][i], 1);
			i++;
		}
	}
	if (parsed[n + 1])
		write(1, " ", 1);
}

void	ft_sticazzi(t_cmd *cmd, char **parsed, int n)
{
	if (!ft_chr(parsed[n], '$', 1))
	{
		echo_dollar_plus(cmd, parsed, n);
		if (parsed[n + 1])
			write(1, "\n", 1);
	}
	else if (parsed[n][0] == '$')
		echo_dollar_plus(cmd, parsed, n);
	else
	{
		parsed[n] = expand_echo(parsed, n);
		echo_dollar(parsed, n, cmd, 0);
	}
}

void	ft_sticazzi2(t_cmd *cmd, char **parsed, int n)
{
	if (!ft_chr(parsed[n], '$', 1))
	{
		echo_dollar_plus(cmd, parsed, n);
		if (parsed[n + 1])
			write(1, "\n", 1);
	}
	else
	{
		parsed[n] = expand_echo(parsed, n);
		echo_dollar(parsed, n, cmd, 1);
	}
}
