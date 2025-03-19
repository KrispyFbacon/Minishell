/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/19 17:33:40 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	quote_changer(char *s, int *i, t_info *info)
{
	if (s[*i] == '\'' && info->mode != DOUBLE_QUO)
	{
		(*i)++;
		if (info->mode == GENERAL)
			info->mode = SINGLE_QUO;
		else if (info->mode == SINGLE_QUO)
			info->mode = GENERAL;
	}
	if (s[*i] == '\"' && info->mode != SINGLE_QUO)
	{
		(*i)++;
		if (info->mode == GENERAL)
			info->mode = DOUBLE_QUO;
		else if (info->mode == DOUBLE_QUO)
			info->mode = GENERAL;
	}
}

void	expand_env(char *s, int *i, t_info *info)
{
	(*i)++;
	ft_printf("Expantion made\n");
	while (s[*i] && s[*i] != "\"" && !(ft_strchr(WHITE_SPACES, s[*i])))
		*i++;
	(*i)--;
}

void general_mode_handler();

void	node_edit(t_shell **shell, t_token **token)
{
	t_info	info;
	char	*s;
	int	i;
	
	info.mode = GENERAL;
	s = (*token)->token;
	i = 0;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			mode_handler(s, &i, &info);
		info.start = i;
		if(info.mode == GENERAL)
			general_mode_handler();
		else if(info.mode == SINGLE_QUO)
			single_quote_handler();
		else if(info.mode == DOUBLE_QUO)
			double_quote_handler();
		i++;
	}
	
}

void	handle_quotes(t_shell **shell)
{
	t_token	*token;

	token = (*shell)->token_list;
	while(token)
	{
		node_edit(shell, &token);
		token = token->next;
	}
} */
void	quote_changer(char *s, int *i, t_info *info)
{
	if (s[*i] == '\'')
	{
		if (info->mode == GENERAL)
			info->mode = SINGLE_QUO;
		else if (info->mode == SINGLE_QUO)
			info->mode = GENERAL;
	}
	else if (s[*i] == '\"')
	{
		if (info->mode == GENERAL)
			info->mode = DOUBLE_QUO;
		else if (info->mode == DOUBLE_QUO)
			info->mode = GENERAL;
	}
	(*i)++;
}

char	*take_var_name(char *s, int *i)
{
	int	start;
	int	len;
	
	start = *i;
	len = 0;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (s[*i] && s[*i] != '\"' && s[*i] != '$'
		&& !(ft_strchr(WHITE_SPACES, s[*i])))
	{
		(*i)++;
		len++;
	}
	return (ft_strndup(&s[start], len));
}
char	*get_env_value(char *var_name, t_env *env_list)
{
	t_env *temp;
	
	temp = env_list;
	while(temp)
	{
		if (ft_strcmp(temp->name, var_name) == 0)
			return(temp->value);
		temp = temp->next;
	}
	return ("");
}

char	*expand_var_in_str(char *s, char *var_value, int i, t_info *info)
{
	char	*new_s;
	int		s_len;
	int		new_len;
	int		var_len;
	int		value_len;

	s_len = ft_strlen(s);
	var_len = i - info->env_start;
	value_len = ft_strlen(var_value);
	new_len = s_len - var_len + value_len;
	new_s = (char *)ft_calloc((new_len + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s, info->env_start);
	ft_strlcpy(new_s + info->env_start, var_value, (value_len + 1));
	ft_strlcpy(new_s + info->env_start + value_len, s + i, (s_len - i + 1));
	new_s[new_len] = '\0';
	return (new_s);
}

void	expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*new_s;
	char	*s;
	
	s = *s_ptr;
	info->env_start = (*i);
	(*i)++;
	var_name = take_var_name(s, i);
	info->env_end = (*i);
	var_value = get_env_value(var_name, shell->env);
	new_s = expand_var_in_str(s, var_value, *i, info);
	free (var_name);
	free (s);
	*s_ptr = new_s;
	(*i) = info->env_start + ft_strlen(var_value);
}

void	node_expand(t_shell **shell, t_token **token)
{
	t_info	info;
	char	*s;
	int	i;
	
	info.mode = GENERAL;
	s = (*token)->token;
	i = 0;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			quote_changer(s, &i, &info);
		else if (s[i] == '$' && info.mode != SINGLE_QUO)
			expand_env(*shell, &s, &i, &info);
		else
			i++;
	}
	(*token)->token = s;
}

void	handle_expantions(t_shell **shell)
{
	t_token	*token;

	token = (*shell)->token_list;
	while(token)
	{
		node_expand(shell, &token);
		token = token->next;
	}
}

void	tokenizer(t_shell **shell, char *input)
{
	t_token	*token_list;

	token_list = NULL;
	token_split_space(&token_list, input);
	if (!token_list)
		return ;
	print_tokens(token_list);
	(*shell)->token_list = token_list;
	(*shell)->head = token_list;
	(*shell)->env = ft_calloc(1, sizeof(t_env));
	(*shell)->env->name = "VAR";
	//(*shell)->env->value = "BACON";
	(*shell)->env->value = "s -";
	(*shell)->env->next = NULL;
	handle_expantions(shell);
	//handle_quotes(shell);
	print_tokens((*shell)->token_list);
	free((*shell)->env);
	(*shell)->env = NULL;
}

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */