#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <strings.h>
#include <signal.h>
#include <stdlib.h>
#include "swim_mill.h"

void sigint_handler(int sig)
{
  signal(SIGQUIT, SIG_IGN);
  kill(-((int)getpid()), SIGQUIT);
  delete_shm_sem();
  my_exit("Recieved SIGINT");
}

void pellet_worker()
{
  pid_t pid;

  if ((pid = fork()) == -1)
    fprintf(stderr, "Fail on creating pellet\n");
  else if (!pid)
    if (execlp("./pellet", "pellet", NULL) == -1)
      my_exit("Fail on launching pellet");
}

void game_loop(key_t k, char *river, int map_lock, int ui)
{
  int begin, curr_time = 0;
  pid_t fish_pid;

  srand(time(NULL));
  if ((fish_pid = fork()) == -1)
    my_exit("Failure on fork");
  else if (!fish_pid)
  {
    if (execlp("./fish", "fish", NULL) == -1)
      my_exit("Fail on launching fish");
  }
  else
  {
    signal(SIGINT, sigint_handler);
    if ((begin = time(NULL)) == (time_t)-1)
      my_exit("Fail on time");
    while (curr_time < 30)
    {
      curr_time = time(NULL) - begin;
      usleep(COORDINATOR_CYCLE);
      if (!(rand() % 5))
        pellet_worker();
      if (!ui)
        print_map(river, map_lock);
    }
    signal(SIGQUIT, SIG_IGN);
    kill(-((int)getpid()), SIGQUIT);
    printf("End of the game\n");
    delete_shm_sem();
  }
}
