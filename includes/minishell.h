/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/06 18:10:24 by frbranda         ###   ########.fr       */
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

// error handler
# define INVALID -1
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define UNKNOWN_COMMAND 127

// token type
# define EXEC 0
# define CMD 1
# define PIPE 2
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
	int				state;
	struct s_token	*next;
}	t_token;
//	t_redir			*redir;

struct	s_pipe
{
	int		type;
	void	*left;
	void	*right;
}	t_pipe;

struct	s_redir
{
	int				type;
	char			*redir;
	struct s_redir	*next;
}	t_pipe;

typedef struct s_shell
{
	t_token			*token_list;
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
void			token_split(t_token **token_list, char *input);
void			tokenizer(t_shell **shell, char *input);

// token_tools.c
t_token			*find_last_token(t_token *token);
t_token			*add_last_token(t_token **token, t_token *new);

// initialize_structs.c
t_token			*initialize_token(char *s, int type);
t_shell			*initialize_shell(void);

///////////////////////////////
//           FREE            //
///////////////////////////////

// free_shell.c
void			free_tokens(t_token **token);
void			free_shell(t_shell	**shell);

// free.c
void			free_char_pp(char **s);

///////////////////////////////
//           PRINT           //
///////////////////////////////

// print_shell.c?

// print_token.c
void			print_tokens(t_token *token);
void			print_tokens_simple(t_token *token);

#endif