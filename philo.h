/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:08:50 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/15 15:34:34 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "stdio.h"
#include "unistd.h"
#include <pthread.h>
#include <sys/time.h>
# include <string.h>
# include <stdbool.h>
#include "stdlib.h"
typedef struct s_philospher t_philospher;
typedef struct s_rules
{
	int				num;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				to_eat;
	long long		t_start;
	int				must_eat;
	pthread_t		monitor;
	t_philospher	**philos;
}	t_rules;


typedef struct s_philospher
{
	int				index;
	bool			alive;
	int				pid;
	int				ate;
	pthread_t		thread;
	pthread_mutex_t *left;
	pthread_mutex_t	*right;
	t_rules			*rules;
}	t_philospher;

int	ft_atoi(const char *nptr);

#endif
