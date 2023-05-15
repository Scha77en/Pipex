/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 01:31:45 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/15 14:17:35 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*head;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	if (!head)
		head = NULL;
	read_and_save(fd, &head);
	if (!head)
		return (NULL);
	line = get_the_line(head);
	if (line[0] == '\0')
	{
		ft_lstclear(head);
		head = NULL;
		free(line);
		return (NULL);
	}
	modify_list(&head);
	return (line);
}

void	read_and_save(int fd, t_list **head)
{
	char		*buff;
	ssize_t		readed;
	t_list		*node;

	readed = 1;
	while (!ft_lstchr((*head), NULL, 1) && readed)
	{
		buff = malloc((BUFFER_SIZE + 1));
		if (!buff)
		{
			free(buff);
			return ;
		}
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1 || readed == 0)
		{
			free(buff);
			return ;
		}
		buff[readed] = '\0';
		node = ft_lstnew(buff, readed);
		ft_lstadd_back(head, node);
		free(buff);
	}
}

char	*get_the_line(t_list *head)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	line = allocate_to_line(head);
	if (!line)
		return (NULL);
	j = 0;
	while (head)
	{
		i = 0;
		while (head->content[i])
		{
			if (head->content[i] == '\n')
			{
				line[j++] = head->content[i];
				break ;
			}
			line[j++] = head->content[i++];
		}
		head = head->next;
	}
	return (line[j] = '\0', line);
}

void	modify_list(t_list **head)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (head == NULL || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast(*head);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc((ft_lstchr(NULL, last->content, 0) - i) + 1);
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	ft_lstclear(*head);
	*head = clean_node;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
