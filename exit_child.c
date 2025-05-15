/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:37:42 by yes               #+#    #+#             */
/*   Updated: 2025/05/15 17:04:40 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// TODO free_tokens -> free_nodes
void	free_tokens_child(t_token **token)
{
	t_token	*temp;

	if (!token || !(*token))
		return ;
	while (*token != NULL)
	{
		temp = (*token)->next;
		free((*token)->token);
		if ((*token)->heredoc)
		{
			free_ref(&(*token)->heredoc->hd_path);
			free_ref(&(*token)->heredoc->delimiter);
			free((*token)->heredoc);
			(*token)->heredoc = NULL;
		}
		free(*token);
		*token = temp;
	}
	(*token) = NULL;
}

void	exit_child(t_shell **shell, int status)
{
	errno = status;
	free_ref(&(*shell)->input);
	if ((*shell)->args)
		free_char_pp_ref(&(*shell)->args);
	// TODO mudar node
	if((*shell)->token_list)
	free_tokens_child(&(*shell)->token_list);
	if ((*shell)->envp)
		free_matriz((*shell)->envp, ft_arrlen((*shell)->envp));
	if ((*shell)->cmd)
		free_matriz((*shell)->cmd, ft_arrlen((*shell)->cmd));
	free_ref(&(*shell)->old_pwd);
	rl_clear_history();
	exit(status);
}