/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:47:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/26 17:45:38 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void philo(t_rules *in)
{
    t_philosophers	**philos;
	int				i;
	int				philo_amount;
	// char			*a;
	// a = malloc(sizeof(char) * 2);
	// a[0]= 0;
	// a[1] = '\0';

	philo_amount = in->philo_amount;
    philos = fill_philo(in);
	in->philos = philos;
	i = 0;
    pthread_create(&in->monitor, NULL, monitor_thread, in);
	if (philo_amount == 1)
	{
		pthread_create(&philos[i]->thread, NULL, single_routine, philos[i]);
		pthread_join(philos[0]->thread, NULL);
		pthread_join(in->monitor, NULL);
		return ;
	}
	while (i < philo_amount)
	{
		pthread_create(&philos[i]->thread, NULL, philos_routine, philos[i]); 
		i++;
	}
	i = 0;
    while (i < philo_amount)
    {
        pthread_join(philos[i]->thread, NULL);
        i++;
    }
	pthread_join(in->monitor, NULL);
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
    // printf("philo_amount: %d\n", in->philo_amount);
    // printf("t_to_die: %lld\n", in->t_to_die);
    // printf("t_to_eat: %lld\n", in->t_to_eat);
    // printf("t_to_sleep: %lld\n", in->t_to_sleep);
    // printf("must_eat: %d\n", in->must_eat);
    philo(in);
    return (0);
}
