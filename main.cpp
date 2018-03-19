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
  defaults.show_refresh_rate = true;
  defaults.brightness = 82;
  defaults.disable_hardware_pulsing = true;

  RGBMatrix *_matrix = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);

  if (_matrix == NULL) {return 1;}

  // Exit signal 
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);
  
  const int threshold_temp = 3;
  const int range_temp = 1;
  array< array<int,3>, 3> states_temp = {{{0,0,0},{220,20,60},{123,104,238}}};

  Cyclic cyclic(_matrix, range_temp, threshold_temp, states_temp, _matrix->width(), _matrix->height());
  
  while(true) {
	cyclic.Run();	
  }

  _matrix->Clear();
  delete _matrix;
  delete &cyclic;
  return 0;
}
