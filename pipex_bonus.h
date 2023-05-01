/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:13:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/01 16:48:07 by aouhbi           ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	manage_first_child(char **argv, int *pipfd, char **env);
void	manage_children(char **argv, int *pipfd, char **env, int j);
void	manage_last_child(char **argv, int *pipfd, char **env, int j);
int		command_search(char **path);
void	error_out(char *msg);
int		command_handler(int argc, char **argv, int *pipfd, char **env);
int		here_doc_management(char **argv, int *pipfd, char **env);
void	manage_heredoc_cmd(char **argv, int *pipfd, char **env);
int		command_handler_heredoc(int argc, char **argv, int *pipfd, char **env);
int		ft_strcmp(const char *s1, const char *s2);
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

#endif