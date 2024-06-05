/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:40:27 by luvallee          #+#    #+#             */
/*   Updated: 2024/01/24 15:53:16 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
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
int					check_endline(t_list **save);
char				*extract_string(t_list *save);
void				delete_and_free(t_list **save);
void				ft_lstadd_back(t_list **lst, char data);
int					ft_lstsize(t_list *lst);
t_list				*save_the_buffer(char *buffer, t_list **save);
#endif