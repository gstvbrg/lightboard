#include "./matrix/include/led-matrix.h"
#include "cyclic.cpp"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <vector>
#include <array>

using namespace rgb_matrix;
using namespace std;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular";  
  defaults.rows = 32;
  defaults.chain_length = 4;
  defaults.parallel = 3;
  defaults.show_refresh_rate = false;
  defaults.brightness = 82;
  defaults.disable_hardware_pulsing = true;

  Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL) {return 1;}

  // Exit signal 
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);
  
  const int threshold_temp = 3;
  array< array<int,3>, 4> states_temp = {{{0,0,0},{0,255,0},{0,0,255},{0,255,0}}};

  Cyclic cyclic(canvas, threshold_temp, states_temp, canvas->width(), canvas->height());
  
  int count = 0;

  while(true) {
	  cyclic.drawStateTo(canvas);
	  cyclic.archiveState();
	  cyclic.updateState();
	  cout << ++count << '\n';
	  usleep(1000);
  }
  
  canvas->Clear();
  delete canvas;
  return 0;
}
