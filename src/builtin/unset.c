/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:06 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/15 15:07:55 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes a specific variable from the shell's environment.
 * 
 * This function searches for a specified environment variable in the shell's
 * environment and removes it if found. After removing the variable, the
 * remaining environment variables are shifted to fill the gap, and the last
 * element is set to `NULL`.
 * 
 * @param var The name of the environment variable to be removed.
 * @param shell The shell structure containing the environment variables.
 */
void	ft_erase_var(char *var, t_shell *shell)
{
	int	i;

	i = get_env_line(var, shell);
	if (i >= 0)
	{
		free (shell->envp[i]);
		while (shell->envp[i])
		{
			shell->envp[i] = shell->envp[i + 1];
			i++;
		}
		shell->envp[i] = NULL;
	}
}

/**
 * @brief Removes environment variables from the shell's environment.
 * 
 * This function handles the `unset` built-in command, which removes one or
 * more environment variables from the shell's environment. If an invalid
 * option is provided, an error message is printed. If valid variables are
 * provided, they are erased from the environment.
 * 
 * @param args The arguments passed to the `unset` command, with the first
 * argument being the command itself, and the subsequent arguments being the
 * environment variables to be removed.
 * @param shell The shell structure containing the environment variables.
 * @return int Returns `0` on success, or an error code if an invalid option is
 * provided.
 */
int	ft_unset(char **args, t_shell *shell)
{
	int		i;
	char	*error;

	i = 0;
	(void)shell;
	if (args[1] && args[1][0] == '-')
	{
		error = ft_strdup_free(ft_strjoin("unset: ", ft_strdup(args[1])),
				ft_strdup(":invalid option\n"));
		if (!error)
			return (errno);
		print_msg_error(error, shell);
		free(error);
	}
	while (args[++i])
		ft_erase_var(args[i], shell);
	return (0);
}
