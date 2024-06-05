/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:15 by luvallee          #+#    #+#             */
/*   Updated: 2024/01/30 15:12:02 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_end_line(t_list **save, int fd)
{
	t_list	*temp;

	if (!*save)
		return (0);
	temp = *save;
	while (temp != NULL && temp->fd != fd)
		temp = temp->next;
	while (temp != NULL && temp->fd == fd)
	{
		if (temp->content == '\n')
			return (1);
		temp = temp->next;
	}
	return (0);
}

char	*extract_string(t_list *save, int fd)
{
	char	*new_str;
	int		len;
	int		i;

	if (search_node(&save, fd, 0) < 0 || !save)
		return (NULL);
	len = ft_lstsize(save, fd);
	new_str = malloc(sizeof(t_list) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (save != NULL && save->fd != fd)
		save = save->next;
	while (save != NULL && save->fd == fd)
	{
		if (save->content == '\n')
		{
			new_str[i++] = '\n';
			break ;
		}
		new_str[i++] = save->content;
		save = save->next;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	search_node(t_list **save, int fd, int pos)
{
	t_list	*temp;
	int		same_fd;

	temp = *save;
	same_fd = 0;
	while (temp != NULL)
	{
		if (temp->fd == fd)
		{
			same_fd = 1;
			break ;
		}
		pos++;
		temp = temp->next;
	}
	while (same_fd == 1 && temp != NULL)
	{
		if (temp->fd != fd)
			return (pos);
		pos++;
		temp = temp->next;
	}
	if (same_fd == 1)
		return (pos);
	return (-1);
}

t_list	*save_the_buffer(char *buffer, t_list **save, int fd)
{
	t_list	*new;
	int		i;
	int		pos;

	i = 0;
	if (*save == NULL)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->content = buffer[i++];
		new->fd = fd;
		save = &new;
		(*save)->next = NULL;
	}
	while (buffer[i])
	{
		pos = search_node(save, fd, 0);
		if (pos > 0 && (*save)->next != NULL)
			insert_node(*save, buffer[i], fd, pos);
		else
			ft_lstadd_back(save, buffer[i], fd);
		i++;
	}
	return (*save);
}

char	*get_next_line(int fd)
{
	static t_list	*save = NULL;
	t_element		element;
	char			*str;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, &str, 0) < 0)
		return (NULL);
	while (check_end_line(&save, fd) == 0)
	{
		element.buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!element.buffer)
			return (NULL);
		element.count = read(fd, element.buffer, BUFFER_SIZE);
		if (element.count == 0 || (int)element.count == -1)
		{
			free(element.buffer);
			break ;
		}
		element.buffer[element.count] = '\0';
		save = save_the_buffer(element.buffer, &save, fd);
		free(element.buffer);
	}
	str = extract_string(save, fd);
	free_the_list(&save, fd);
	return (str);
}

// #include <stdio.h>
// #include <fcntl.h>
// #include <sys/stat.h>
// int	main(void)
// {
// 	int fd1;
// 	int fd2;
// 	char *str1;
// 	char *str2;
// 	char *str3;
// 	char *str4;
// 	fd1 = open("test/fd1", O_RDONLY);
// 	if (fd1 == -1)
// 		return (-1);
// 	fd2 = open("test/fd2", O_RDONLY);
// 	if (fd2 == -1)
// 		return (-1);
// 	int fd3 = open("test/fd3", O_RDONLY);
// 	if (fd3 == -1)
// 		return (-1);
// 	int fd4 = open("test/fd4", O_RDONLY);
// 	if (fd4 == -1)
// 		return (-1);
// 	while (1)
// 	{
// 		str1 = get_next_line(fd1);
// 		printf("fd1 : %s", str1);
// 		free(str1);
// 		str2 = get_next_line(fd2);
// 		printf("fd2 : %s", str2);
// 		free(str2);
// 		str3 = get_next_line(fd3);
// 		printf("fd3 : %s", str3);
// 		free(str3);
// 		str4 = get_next_line(fd4);
// 		printf("fd4 : %s", str4);
// 		free(str4);
// 		if (str1 == NULL && str2 == NULL && str3 == NULL && str4 == NULL)
// 		{
// 			free(str1);
// 			free(str2);
// 			free(str3);
// 			free(str4);
// 			break ;
// 		}
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	return (0);
// }