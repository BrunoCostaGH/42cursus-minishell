/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:02:42 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/21 18:02:54 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chrjoin(char c1, char c2)
{
	char	*str;

	if (!c1 || !c2)
		return (0);
	str = ft_calloc(3, sizeof(char));
	if (!str)
		return (0);
	str[0] = c1;
	str[1] = c2;
	return (str);
}
