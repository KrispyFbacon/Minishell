/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/11 18:20:06 by frbranda         ###   ########.fr       */
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

//
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
# define EXEC 0
# define CMD 1
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
	char			*var;	// $USER
	char			*value;	// frbranda
	struct t_env	*next;
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

typedef struct	s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;

typedef struct	s_redir
{
	char			*redir;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int		type;
	char	**args;
	t_redir	*redirs; 
} t_cmd;

typedef struct s_shell
{
	t_token			*token_list;
	t_env			*env_var;
	int				exit_status;
}	t_shell;

typedef struct s_info
{
	int start;
	int type;
	int mode;
}	t_info;

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

///////////////////////////////
//          PARSING          //
///////////////////////////////

// tokenizer.c
void	token_quote_changer(char *input, int i, t_info *info);
void	token_end_of_word(char *input, int *i, t_info *info);
void	add_token(t_token **token_list, char *input, int i, t_info *info);
void	token_word_handler(t_token **token_list, char *input, int *i, int type);
void	token_redir_handler(t_token **token_list, char *input, int *i);
void	token_pipe_handler(t_token **token_list, char *input, int *i);
void	token_space_handler(t_token **token_list, char *input);
void	tokenizer(t_shell **shell, char *input);

// token_tools.c
t_token	*find_last_token(t_token *token);
t_token	*add_last_token(t_token **token, t_token *new);
int		get_token_type(char *input, int i);

// token_handler.c
/* void	handle_quotes(char *input, int *i, int *start, int *mode);
void	add_token_word(t_token **token_list, char *input, int start, int i);
void	add_token(t_token **token_list, char *input, int i, t_stupid *info);
void	handle_token_redir(t_token **token_list, char *input, int *i);
void	handle_token_pipe(t_token **token_list, char *input, int *i); */

// initialize_structs.c
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
void		print_tokens(t_token *token);
void		print_tokens_simple(t_token *token);

#endif