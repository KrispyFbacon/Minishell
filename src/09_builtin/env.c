/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:45 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 23:23:59 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_error(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == '-' && arg[1])
	{
		ft_printf_fd(2, "env: illegal option -- %c\n", arg[1]);
		return (125);
	}
	else
	{
		ft_printf_fd(2, "env: '%s': No such file or directory\n", arg);
		return (127);
	}
}

int	ft_env(char **args, t_shell *shell)
{
	int	i;

	(void)args;
	i = -1;
	if (!shell->envp)
		return (0);
	if (args[1])
		env_error(args[1]);
	else
	{
		while (shell->envp[++i])
		{
			if (ft_strchr(shell->envp[i], '='))
				ft_printf_fd(1, "%s\n", shell->envp[i]);
		}
	}
	return (0);
}
