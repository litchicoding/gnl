/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:24 by luvallee          #+#    #+#             */
/*   Updated: 2024/01/30 14:48:23 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_lstsize(t_list *lst, int fd)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	if (search_node(&lst, fd, 0) > 0)
	{
		while (lst != NULL && lst->fd != fd)
			lst = lst->next;
	}
	while (lst != NULL && lst->fd == fd)
	{
		if (lst->content == '\n')
			return (i + 1);
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstadd_back(t_list **lst, char data, int fd)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = data;
	new->next = NULL;
	new->fd = fd;
	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	insert_node(t_list *save, char data, int fd, int pos)
{
	t_list	*new;
	t_list	*current;
	t_list	*next_node;
	int		i;

	if (!save)
		return ;
	i = 0;
	current = save;
	while (i++ < (pos - 1) && current != NULL)
		current = current->next;
	if (current == NULL)
	{
		ft_lstadd_back(&save, data, fd);
		return ;
	}
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	next_node = current->next;
	new->content = data;
	new->fd = fd;
	current->next = new;
	new->next = next_node;
}

t_list	*delete_node(t_list *temp)
{
	t_list	*next;

	if (temp->content != '\n')
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	return (temp);
}

void	free_the_list(t_list **save, int fd)
{
	t_list	*temp;
	t_list	*prev;

	prev = NULL;
	temp = *save;
	while (temp != NULL)
	{
		if (temp->fd == fd)
		{
			if (prev == NULL)
				*save = temp->next;
			else
				prev->next = temp->next;
			if (temp->content == '\n')
				return (free(temp));
			else
				temp = delete_node(temp);
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}
