/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/03 21:02:03 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//# include "free.h"
//# include "tokens.h"

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/

// all special cases
# define SPECIAL " \t\r\n\v\f\"\'<>|"
# define WHITE_SPACES " \t\r\n\v\f"
# define OPERATOR "<>|"
# define T_REDIR "<>"
# define T_PIPE "|"
# define QUOTES "\"\'"

// error handler
# define INVALID -1
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define UNKNOWN_COMMAND 127

// token type
# define CMD 0
# define ARG 1
# define PIPE 2
# define REDIR_IN 4// < redir onto a file and chage its contente
# define REDIR_OUT 5// >
# define APPEND 6// >> redir onto a file and add content
# define HEREDOC 7// <<

# define FALSE 0
# define TRUE 1

// Quote handle
# define GENERAL 0	
# define SINGLE_QUO 1
# define DOUBLE_QUO 2

/*=============================================================================#
#                               STRUCTS                                        #
#=============================================================================*/

typedef struct s_env
{
	char			*name;	// $USER
	char			*value;	// frbranda
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	int				type;	//EXEC/CMD/PIPE/REDIR
	struct s_token	*next;
}	t_token;

/*typedef enum Redir {
	INPUT,
	OUTPUT
}	Redir_e;*/

typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;

typedef struct s_redir
{
	char			*redir;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int		type;
	char	**args;
	t_redir	*redirs;
}	t_cmd;

// struct helper
typedef struct s_info
{
	int	start;
	int	end;
	int	len;
	int	env_start;
	int	env_end;
	int	type;
	int	type_flag;
	int	mode;
	int	error_flag;
}	t_info;

typedef struct s_shell
{
	t_token	*token_list;
	t_token	*head;
	t_env	*env;
	t_info	info;
	int		pid;
	char	*s_pid;
	int		exit_status;
}	t_shell;


/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

///////////////////////////////
//          PARSING          //
///////////////////////////////

//TODO ORGANIZE THIS v
void	inizialize_info(t_info	*info);
int		ft_has_white_spaces(char *s);

// tokenizer.c
void	tokenizer(t_shell **shell, char *s);

// 00_handle_spaces
//  token_split_space.c
void	token_word_handler(char *s, int *i, t_info *info);
void	token_redir_handler(char *s, int *i, t_info *info);
void	split_spaces(t_token *token_list, char *s, int *i, t_info *info);

//  type_helper.c
void	get_token_redir_type(char *s, int i, t_info *info);
void	get_token_type(t_token *token_list, t_info *info);

// 01_handle_expansions
//  handle_expansions.c
char	*expand_variable(t_shell *shell, char **s_ptr, int *i, t_info *info);
int		expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info);
int		handle_expansions(t_shell *shell, char **s_ptr, int *i, t_info *info);

//  handle_dollar_cases.c
char	*remove_dollar(char **s_ptr, int *i, t_info *info);
char	*handle_double_dollar(t_shell *shell, char *s, int *i, t_info *info);
char	*handle_question_mark(t_shell *shell, char *s, int *i, t_info *info);

//  expansion_helper.c
char	*take_var_name(char *s, int *i);
char	*get_env_value(char *var_name, t_env *env_list);
char	*expand_var_in_str(char *s, char *var_value, int i, t_info *info);

// 02_handle_quotes
//	handle_quote.c
void	remove_quotes(char *s, int i, t_info *info);
void	handle_quotes(char **s_ptr, int *i, t_info *info);

//  quote_helper.c
void	quote_changer(char *s, int *i, t_info *info);

// 03_add_new_token
//  add_new_token.c
t_token	*add_new_token(t_token **token_list, char *temp, t_info *info);

// token_tools.c
t_token	*find_last_token(t_token *token);
t_token	*add_last_token(t_token **token, t_token *new);

// initialize_structs.c
// TODO DELETE initialize_env (or cnahge it when )
t_env	*initialize_env(void);
t_token	*initialize_token(char *s, int type);
t_shell	*initialize_shell(void);

///////////////////////////////
//           FREE            //
///////////////////////////////

// free_shell.c
void	free_tokens(t_token **token);
void	free_shell(t_shell	**shell);

// free.c
void	free_char_pp(char **s);

///////////////////////////////
//           PRINT           //
///////////////////////////////

// print_shell.c?

// print_token.c
void	print_type(t_info *info);
void	print_tokens(t_token *token);
void	print_tokens_simple(t_token *token);

#endif