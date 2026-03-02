/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abecucci <abecucci@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:44:41 by abecucci          #+#    #+#             */
/*   Updated: 2026/03/02 20:39:24 by abecucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_UTILS_H
# define PHILOSOPHERS_UTILS_H

/* --- STRUTTURE --- */
typedef enum e_bool		t_bool;
typedef struct s_shared	t_shared;
typedef struct s_philo	t_philo;


/* --- FUNZIONI --- */
int64_t			time_now_ms(void);
void			print_state(t_philo *p, const char *state);
void			raise_stop(t_shared *sh);
t_bool			should_stop(t_shared *sh);


#endif //PHILOSOPHERS_UTILS_H