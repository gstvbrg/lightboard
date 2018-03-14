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

  std::vector<int> births_temp = {1,3,4,5};
  std::vector<int> deaths_temp = {2,8,9};
  std::vector< array<int,3> > states_temp = {{123,456,124},{123,564,234},{192,233,255}};

  Cyclic cyclic(canvas, births_temp, deaths_temp, states_temp);

  canvas->Clear();
  delete canvas;
  return 0;
}
