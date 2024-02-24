/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:45:42 by pipolint          #+#    #+#             */
/*   Updated: 2024/02/24 20:17:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}
