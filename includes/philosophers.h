//
// Author: Marwane Khsime 
// Date: 2017-03-16 20:02:17 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 20:02:17
//

#ifndef _PHILOSOPHERS_H_
# define _PHILOSOPHERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

typedef enum {
    UNDEFINED = -1,
    EAT = 0,
    THINK = 1,
    SLEEP = 2
}      Action;

typedef struct		s_philos {
  int			id;
  Action		lastAction;
  pthread_t		thread;
  pthread_mutex_t	chopstick;
}			t_philos;

typedef struct		s_manager {
  struct s_philos	*philos;
  int			nbPhilos;
  int			nbChopsticks;
  int			mealsLimit;
  bool			limitReached;
}			t_manager;

#endif /* _PHILOSOPHERS_H_ */
