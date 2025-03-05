/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/05 18:48:05 by yes              ###   ########.fr       */
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

# define SIZE 85

// error handler
# define INVALID -1
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define UNKNOWN_COMMAND 127

// token_tree
# define EXEC 0
# define CMD 1
# define PIPE 2
# define REDIR 3

// token
# define ARG 0
# define BUILTIN 1
# define ENV 2
# define TK_PIPE 3 // |
# define REDIR_RIGHT 4// > redir onto a file and chage its contente
# define REDIR_LEFT 5// <
# define APPEND 6// >> redir onto a file and add content
# define HEREDOC 7// <<

# define FALSE 0
# define TRUE 1

// Quote handle
# define GENERAL 0	//change to NORMAL?
# define SINGLE_QUO 1
# define DOUBLE_QUO 2

/*=============================================================================#
#                               STRUCTS                                        #
#=============================================================================*/

typedef struct s_env
{
	char			*var;	// $USER
	char			*value;	// frbranda
	struct t_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	int				type;	// EXEC/CMD/PIPE/REDIR
	int				state;	// GENERAL / SINGLE_QUO / DOUBLE_QUO
	struct s_token	*prev; // Delete
	struct s_token	*next;
}	t_token;
//	t_redir			*redir;

typedef struct s_token_tree
{
	t_token				*token_list;
	int					type;
	struct s_token_tree	*left;
	struct s_token_tree	*right;
}	t_token_tree;

typedef struct s_shell
{
	t_token_tree	*token_tree;
	t_env			*env_var;
	int				exit_status;
}	t_shell;
/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

///////////////////////////////
//          PARSING          //
///////////////////////////////

// tokenizer.c
int				var_len(char *input, int *i);
int				get_len(char *input,int *i,int mode);
char			*new_string(char *input, int *i, int mode);
void			token_add(t_token **token, char *input, int *i);
void			token_split(t_token_tree **token_list, char *input);
void			tokenizer(t_shell **shell, char *input);

// token_tools.c
t_token			*find_last_token(t_token *token);
t_token			*add_last_token(t_token **token, t_token *new);

// token_list_tools.c
t_token_tree	*find_last_node(t_token_tree *token);
t_token_tree	*add_last_node(t_token_tree **token, t_token_tree *new);

// initialize_structs.c
t_token			*initialize_token(char *s, int type);
t_token_tree	*initialize_token_list(void);
t_shell			*initialize_shell(void);

///////////////////////////////
//           FREE            //
///////////////////////////////

// free_shell.c
void			free_tokens(t_token **token);
void			free_token_list(t_token_tree **token_list);
void			free_shell(t_shell	**shell);

// free.c
void			free_char_pp(char **s);

///////////////////////////////
//           PRINT           //
///////////////////////////////

// print_shell.c?

// print_token_list.c
void			print_token_list(t_token_tree *token_list);
void			print_token_list_simple(t_token_tree *token);

// print_token.c
void			print_tokens(t_token *token);
void			print_tokens_simple(t_token *token);



///////////////////////////////
//          OUTDATED         //
///////////////////////////////

/* // tokenizer.c
char			*new_string(char *input, int *i);
void			handle_string_to_node(
					t_token_tree **token_list, char *input, int *i);
void			node_split(t_token_tree **token_list, char *input);
void			tokenizer(t_shell **shell, char *input);

// token_list_tools.c
t_token_tree	*find_last_node(t_token_tree *token);
t_token_tree	*add_last_node(t_token_tree **token, t_token_tree *new);
t_token_tree	*find_last_pipe(t_token_tree *token);
t_token_tree	*add_pipe_to_node(t_token_tree **token, t_token_tree *new);

// initialize_structs.c
t_token			*initialize_tokens(char *s);
t_token_tree	*initialize_token_list(char *s, int type);
t_shell			*initialize_shell(void); */

/* // print_token_list.c
void			print_token_list(t_token_tree *token);
void			print_token_list_simple(t_token_tree *token);

// print_token.c
void			print_tokens(t_token *token);
void			print_tokens_simple(t_token *token); */

///////////////////////////////
//            OLD            //
///////////////////////////////

/* // OLD TOKENIZER
// tokenizer.c
void	token_split(t_token **token,char *input);
void	tokenizer(char *input);

// token_tools.c
t_token	*initialize_token(char *input);
t_token	*find_last_token(t_token *token);
t_token	*list_add_last_token(t_token **token, t_token *new);

// print_token.c
void	print_token_list(t_token *token);
void	print_tokens(t_token *token); */

#endif