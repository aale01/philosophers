/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:35:48 by abecucci          #+#    #+#             */
/*   Updated: 2026/02/17 18:02:56 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	time_now_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	// printf("usec: %ld\n", tv.tv_usec);
	// printf("sec: %ld\n", tv.tv_sec);
	// printf("time: %ld\n", tv.tv_sec * 1000000 + tv.tv_usec);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}