/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Schatten <Schatten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:30:47 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/18 05:08:02 by Schatten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	manage_heredoc_first(char **argv, int *pipfd, char **env, char *data)
{
	char	**cmd;
	char	**path;
	int		fd;
	int		ret;
	int		i;

	fd = writing_data(data);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2", 0);
	close(pipfd[1]);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_out("dup2", 0);
	close(fd);
	cmd = ft_split(argv[3], ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve", 0);
}

int	command_handler_heredoc(int argc, char **argv, int *pipfd, char **env)
{
	int		cmd_n;
	pid_t	pid_b;
	int		j;

	cmd_n = argc - 6;
	j = 4;
	while (cmd_n > 0)
	{
		pid_b = fork();
		if (pid_b == 0)
			manage_children(argv, pipfd, env, j);
		else
			waitpid(pid_b, NULL, 0);
		j++;
		cmd_n--;
	}
	return (j);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	command_search(char **path)
{
	int		i;

	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
			return (i);
	}
	perror("Command Not Found");
	exit(EXIT_FAILURE);
}

char	*get_data(char **argv)
{
	char	*line;
	char	*data;

	data = malloc(1);
	data[0] = '\0';
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (ft_strcmp_herdoc(line, argv[2]) == 0)
			break ;
		data = ft_strjoin(data, line);
		free(line);
	}
	return (free(line), data);
}
