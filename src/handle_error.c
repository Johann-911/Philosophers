/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:49:00 by jtoumani          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:39 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wrong_input()
{
	printf("         wrong input \n");
	printf(" -------------------------------\n");
	printf("|        u need 4 inputs        |\n");
	printf("| 1. nbr of philos              |\n");
	printf("| 2. time to die (in ms)        |\n");
	printf("| 3. time to eat (in ms)        |\n");
	printf("| 4. time to sleep (in ms)      |\n");
	printf("| 5. (optinal) max times to eat |\n");
	printf("|         try again   :)        |\n");
	printf(" -------------------------------");	
}