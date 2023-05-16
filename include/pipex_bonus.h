/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Schatten <Schatten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:13:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/16 22:06:23 by Schatten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	**ft_split(char *s, char c);
char	*ft_strjoin_b(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	manage_first_child(char **argv, int *pipfd, char **env);
void	manage_children(char **argv, int *pipfd, char **env, int j);
void	manage_last_child(char **argv, int *pipfd, char **env, int j);
int		command_search(char **path);
void	error_out(char *msg, int v);
int		command_handler(int argc, char **argv, int *pipfd, char **env);
void	here_doc_management(int argc, char **argv, int *pipfd, char **env);
void	manage_heredoc_first(char **argv, int *pipfd, char **env, char *data);
int		command_handler_heredoc(int argc, char **argv, int *pipfd, char **env);
int		ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);
void	read_and_save(int fd, t_list **head);
char	*get_the_line(t_list *head);
void	modify_list(t_list **head);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *content, ssize_t readed);
int		ft_lstchr(t_list *head, char *s, int v);
char	*allocate_to_line(t_list *stash);
void	ft_lstclear(t_list *lst);
char	*get_data(char **argv);
int		ft_strcmp_herdoc(char *s1, char *s2);
int		writing_data(char *data);
char	*generate_file(void);
char	**find_path(char **env);
int		get_env_path(char **env);
int		ft_strncmp(char *s1, char *s2, int n);
void	waiting_und_closing(pid_t pid1, pid_t pid2, int *pipfd);

#endif