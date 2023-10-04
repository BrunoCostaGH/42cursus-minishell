/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:57:54 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/02 15:56:37 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*previous_history(t_readline *rl_data)
{
	unsigned int	index;
	t_list			*lst;

	if (rl_data->history_offset >= (unsigned int)ft_lstsize(*rl_data->history))
		return (0);
	index = 0;
	rl_data->history_offset++;
	lst = *rl_data->history;
	while (lst && ++index < rl_data->history_offset)
		lst = lst->next;
	return (lst->content);
}

char	*next_history(t_readline *rl_data)
{
	unsigned int	index;
	t_list			*lst;

	if (!rl_data->history_offset || \
		(rl_data->history_offset && !--rl_data->history_offset))
		return (0);
	index = 0;
	lst = *rl_data->history;
	while (lst && ++index < rl_data->history_offset)
		lst = lst->next;
	return (lst->content);
}

void	m_rl_clear_history(void *p_data)
{
	static t_readline	*rl_data;

	if (!rl_data || p_data)
	{
		if (!rl_data && p_data)
			rl_data = (t_readline *)p_data;
		return ;
	}
	if (rl_data->history)
	{
		ft_lstclear(rl_data->history, &free);
		free(rl_data->history);
	}
	rl_data->history = 0;
}

void	ft_rl_clear_history(void)
{
	m_rl_clear_history(0);
}

void	m_add_history(void *p_data, char *string)
{
	static t_readline	*rl_data;

	if (!rl_data || p_data)
	{
		if (!rl_data && p_data)
		{
			rl_data = (t_readline *)p_data;
			rl_data->history = ft_calloc(1, sizeof(t_list *));
		}
		return ;
	}
	ft_lstadd_front(rl_data->history, ft_lstnew(ft_strdup(string)));
}

void	ft_add_history(char *string)
{
	m_add_history(0, string);
}
