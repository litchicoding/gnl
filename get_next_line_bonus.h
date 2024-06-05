/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:57:21 by luvallee          #+#    #+#             */
/*   Updated: 2024/01/30 14:56:37 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	int				fd;
	char			content;
	struct s_list	*next;
}					t_list;

# ifndef T_ELEMENT
#  define T_ELEMENT

typedef struct s_element
{
	size_t			count;
	char			*str;
	char			*buffer;
}					t_element;
# endif

char				*get_next_line(int fd);
int					check_end_line(t_list **save, int fd);
char				*extract_string(t_list *save, int fd);
int					search_node(t_list **save, int fd, int pos);
void				free_the_list(t_list **save, int fd);
void				ft_lstadd_back(t_list **lst, char data, int fd);
int					ft_lstsize(t_list *lst, int fd);
void				insert_node(t_list *lst, char data, int fd, int pos);
t_list				*delete_node(t_list *temp);
t_list				*save_the_buffer(char *buffer, t_list **save, int fd);
#endif