/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:08:50 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/22 15:09:17 by nfakih           ###   ########.fr       */
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

typedef struct s_philospher t_philosophers;
typedef struct s_rules
{
	int				num;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				to_eat;
	long long		t_start;
	int				must_eat;
	long long		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		monitor;
	t_philosophers	**philos;
	pthread_mutex_t *forks;
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
}	t_philosophers;

int		ft_atoi(const char *nptr);
void	*philos_routine(void *arg);
#endif
