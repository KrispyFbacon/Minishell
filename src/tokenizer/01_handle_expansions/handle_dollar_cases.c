/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:50:52 by yes               #+#    #+#             */
/*   Updated: 2025/03/30 16:36:11 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dollar(char **s_ptr, int *i, t_info *info)
{
	char	*new_s;
	char	*s;

	s = *s_ptr;
	new_s = expand_var_in_str(s, "", *i, info);
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
	*i = info->env_start + pid_len;
	return (new_s);
}

char	*handle_question_mark(t_shell *shell, char *s, int *i, t_info *info)
{
	char	*new_s;
	char	*exit_status;
	int		exit_status_len;

	exit_status = ft_itoa(shell->exit_status);
	exit_status_len = ft_strlen(exit_status);
	info->env_end = (*i) + 1;
	new_s = expand_var_in_str(s, exit_status, info->env_end, info);
	if (new_s)
	{
		free(exit_status);
		return (new_s);
	}
	*i = info->env_start + exit_status_len;
	return (s);
}
