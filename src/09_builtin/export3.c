/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:36 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 23:38:14 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(char **envp)
{
	char	**new_envp;
	int		i;
	int		len;

	len = ft_arrlen(envp);
	i = 0;
	new_envp = ft_calloc(len + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	new_envp[i + 1] = NULL;
	free_char_pp_ref(&envp);
	return (new_envp);
}

int	update_existing_var(char *new_var, t_shell *shell, int i)
{
	if (i >= 0)
	{
		free(shell->envp[i]);
		shell->envp[i] = new_var;
		return (0);
	}
	return (-1);
}

char	*get_value(char *var)
{
	char	*value;
	int		i;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	value = ft_strdup(var + i + 1);
	if (!value)
		return (ft_strdup(""));
	return (value);
	ft_printf_fd(1, "value: %s\n", value); //TODO: is this to delete ???
}

void	concatenate_value(char **var, char *new_var, t_shell *shell, int i)
{
	char	*new_value;
	char	*old_value;

	old_value = get_value(shell->envp[i]);
	new_value = ft_strdup(ft_strnstr(*var, "+=", ft_strlen(*var)) + 2);
	if (*var)
		free_ref(var);
	*var = ft_strdup_free(ft_strjoin(new_var, "="),
			ft_strdup_free(old_value, new_value));
	free(shell->envp[i]);
	shell->envp[i] = ft_strdup(*var);
	free_ref(&new_var);
	free_ref(var);
}
