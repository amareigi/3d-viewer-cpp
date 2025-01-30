#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets>

#include "main_widget.h"

namespace s21 {
class View {
 private:
  Controller* m_p_controller_;
  int m_argc;
  char** m_pp_argv;

 public:
  View(Controller* c, int argc, char** argv);
  int startEventLoop();
};
}  // namespace s21
#endif  // VIEW_H
