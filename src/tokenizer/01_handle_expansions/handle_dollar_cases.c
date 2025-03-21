/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:50:52 by yes               #+#    #+#             */
/*   Updated: 2025/03/21 16:29:22 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dollar(char **s_ptr, int *i, t_info *info)
{
	char	*new_s;
	char	*s;

	s = *s_ptr;
	new_s = expand_var_in_str(s, "", *i, info);
	free(s);
	*s_ptr = new_s;
	*i = info->env_start;
	return (new_s);
}

char	*handle_double_dollar(t_shell *shell, char *s, int *i, t_info *info)
{
	char	*new_s;
	int		pid_len;

	pid_len = ft_strlen(shell->s_pid);
	info->env_end = (*i) + 1;
	new_s = expand_var_in_str(s, shell->s_pid, info->env_end, info);
	free(s);
	*i = info->env_start + pid_len;
	return (new_s);
}