#include "view/view.h"
int main(int argc, char** argv) {
  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller, argc, argv);
  return view.startEventLoop();
}
