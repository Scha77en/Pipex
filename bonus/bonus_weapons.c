/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:15:44 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/15 23:24:26 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	command_handler(int argc, char **argv, int *pipfd, char **env)
{
	int		cmd_n;
	pid_t	pid_b;
	int		j;

	cmd_n = argc - 5;
	j = 3;
	while (cmd_n > 0)
	{
		pid_b = fork();
		if (pid_b == 0)
			manage_children(argv, pipfd, env, j);
		else
			wait(0);
		j++;
		cmd_n--;
	}
	return (j);
}

int	ft_strcmp_herdoc(char *s1, char *s2)
{
	size_t	i;
	int		v;

	v = 0;
	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[0] == '\n')
			v = 1;
		if (s1[i] == '\n' && v == 0)
			break ;
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	error_out(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
