/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:57:54 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/01 20:01:25 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

//TODO fix logic, not working.
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

void	rl_clear_history(void)
{
	m_rl_clear_history(0);
}

//TODO fix logic, not working.
void	m_add_history(void *p_data, char *string)
{
	static t_readline	*rl_data;
	t_list				**temp;

	if (!rl_data || p_data)
	{
		if (!rl_data && p_data)
		{
			rl_data = (t_readline *)p_data;
			rl_data->history = ft_calloc(1, sizeof(t_list *));
		}
		return ;
	}
	temp = ft_calloc(((sizeof(rl_data->history) / sizeof(t_list *)) + 1), \
		sizeof(t_list *));
	*temp = *rl_data->history;
	ft_lstadd_front(temp, ft_lstnew(string));
	if (rl_data->history)
	{
		ft_lstclear(rl_data->history, &free);
		free(rl_data->history);
	}
	rl_data->history = temp;
	for (t_list *p_history = (*rl_data->history); p_history;)
	{
		ft_printf("%s\n", p_history->content);
		p_history = p_history->next;
	}
}

void	add_history(char *string)
{
	m_add_history(0, string);
}
