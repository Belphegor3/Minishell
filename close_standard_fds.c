/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_standard_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:08:04 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/13 14:08:05 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	close_standard_fds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
