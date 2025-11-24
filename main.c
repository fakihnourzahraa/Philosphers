/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:47:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/23 19:50:37 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void philo(t_rules *in)
{
    t_philosophers	**philos;
	int				i;
	int				num;

	num = in->num;
    philos = init_philo(in);
	i = 0;
    pthread_create(&in->monitor, NULL, monitor_routine, in);
	if (num == 0)
	{
		pthread_create(&philos[i]->thread, NULL, philos_routine, &philos[i]);
	}
	while (i < num)
	{
		pthread_create(&philos[i]->thread, NULL, philos_routine, &philos[i]); 
		i++;
	}
}

int main(int argc, char **argv)
{
	t_rules			*in;
	t_philosophers	**philos;

    if (argc != 6 && argc != 5)
        return (1);
    in = init_in();
    if (!fill_in(in, argv))
        return (1);
    printf("num: %d\n", in->num);
    printf("t_to_die: %lld\n", in->t_to_die);
    printf("t_to_eat: %lld\n", in->t_to_eat);
    printf("t_to_sleep: %lld\n", in->t_to_sleep);
    printf("must_eat: %d\n", in->must_eat);
    philo(in);
    return (0);
}
