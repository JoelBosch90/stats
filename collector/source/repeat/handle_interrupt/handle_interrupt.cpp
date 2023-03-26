#include "handle_interrupt.h"
#include <cstdlib>
#include <signal.h>
using namespace std;

void interrupt_handler(int signal)
{
  exit(signal);
}

void handle_interrupt()
{
  struct sigaction sigint_action;

  sigint_action.sa_handler = interrupt_handler;
  sigemptyset(&sigint_action.sa_mask);
  sigint_action.sa_flags = 0;

  sigaction(SIGINT, &sigint_action, nullptr);
}