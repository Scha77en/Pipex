/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:13:03 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/01 16:09:47 by aouhbi           ###   ########.fr       */
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

char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	manage_first_child(char **argv, int *pipfd, char **env);
void	manage_children(char **argv, int *pipfd, char **env, int j);
void	manage_last_child(char **argv, int *pipfd, char **env, int j);
int		command_search(char **path);
void	error_out(char *msg);
int		command_handler(int argc, char **argv, int *pipfd, char **env);
void	here_doc_management(int argc, char **argv, int *pipfd, char **env);
void	manage_heredoc_cmd(char **argv, int *pipfd, char **env, char *data);
int		command_handler_heredoc(int argc, char **argv, int *pipfd, char **env);

#endif