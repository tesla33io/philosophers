/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:01:59 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/18 22:15:36 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"
#include "../../inc/colors.h"

#include <unistd.h>

int	mutex_init_failed(char *file, char *func)
{
	write(2, RED, ft_strlen(RED));
	write(2, "mutex init failed at ", 21);
	write(2, file, ft_strlen(file));
	write(2, ":", 1);
	write(2, func, ft_strlen(func));
	write(2, R, ft_strlen(R));
	write(2, "\n", 1);
	return (FAIL);
}

int	malloc_failed(char *file, char *func)
{
	write(2, RED, ft_strlen(RED));
	write(2, "malloc failed at ", 17);
	write(2, file, ft_strlen(file));
	write(2, ":", 1);
	write(2, func, ft_strlen(func));
	write(2, R, ft_strlen(R));
	write(2, "\n", 1);
	return (FAIL);
}
