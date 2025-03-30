/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:37:38 by yes               #+#    #+#             */
/*   Updated: 2025/03/30 19:40:19 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO change header ^

#include "minishell.h"

void	get_token_redir_type(char *s, int i, t_info *info)
{
	if (ft_strchr(T_REDIR, s[i]))
	{
		if (s[i] == '>' && s[i + 1] != '>')
			info->type = REDIR_OUT;
		else if (s[i] == '<' && s[i + 1] != '<')
			info->type = REDIR_IN;
		else if (s[i] == '>' && s[i + 1] == '>')
			info->type = APPEND;
		else if (s[i] == '<' && s[i + 1] == '<')
			info->type = HEREDOC;
	}
}

void	get_token_type(t_token *token_list, t_info *info)
{
	t_token	*last;

	if (info->type_flag == TRUE)
		return ;
	if (!token_list)
	{
		info->type = CMD;
		return ;
	}
	last = find_last_token(token_list);
	if (last->type == PIPE)
		info->type = CMD;
	else
		info->type = ARG;
}
