/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 02:00:39 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/16 21:19:49 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	writing_data(char *data)
{
	int		fd;
	char	*info;

	info = generate_file();
	fd = open(info, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		error_out("open", 0);
	write (fd, data, ft_strlen(data));
	close(fd);
	fd = open(info, O_RDONLY, 0777);
	if (fd == -1)
		error_out("open", 0);
	if (unlink(info) == -1)
		perror("Error deleting file");
	return (fd);
}

char	*generate_file(void)
{
	int		i;
	int		j;
	char	*info;
	char	*new_name;
	char	*characters;

	characters = "HiddenabcdefghijklmnopqrstuvwxyzABCDE\
				FGHIJKLMNOPQRSTUVWXYZ0123456789";
	j = 0;
	info = ".Hidden";
	while (1)
	{
		i = 1;
		new_name = malloc(ft_strlen(info) + 1);
		new_name[0] = '.';
		while (info[i] != '\0')
		{
			new_name[i++] = characters[j++];
			if (characters[j] == '\0')
				j = 0;
		}
		new_name[i] = '\0';
		if (access(new_name, F_OK) != 0)
			break ;
	}
	return (new_name);
}
