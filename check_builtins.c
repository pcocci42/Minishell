/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:34:16 by pcocci            #+#    #+#             */
/*   Updated: 2023/07/04 12:44:42 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_cmds(char **parsed, int j)
{
	if (!parsed[j])
		return (1);
	if (ft_strcmp(parsed[j], "exit") == 0)
		return (0);
	else if (ft_strcmp(parsed[j], "cd") == 0)
		return (0);
	else if (ft_strcmp(parsed[j], "export") == 0)
		return (0);
	else if (ft_strcmp(parsed[j], "pwd") == 0)
		return (0);
	else if (ft_strcmp(parsed[j], "echo") == 0)
		return (0);
	else if (ft_strcmp(parsed[j], "unset") == 0)
		return (0);
	else if (ft_strcmp(parsed[j], "env") == 0)
		return (0);
	return (1);
}
