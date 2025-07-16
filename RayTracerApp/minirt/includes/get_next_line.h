/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:47:35 by haaghaja          #+#    #+#             */
/*   Updated: 2025/07/05 17:02:35 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
int		gnl_get_line(char **str, char *buffer);
int		gnl_strjoin(char *str1, char *str2);
char	*gnl_new_str(char *str, ssize_t bytes_read);
char	*gnl_exit(char *str, char *buffer);
void	gnl_shift_buffer(char *buffer);	
#endif
