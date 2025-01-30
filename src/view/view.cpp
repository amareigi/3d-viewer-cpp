#include "view.h"

#include <QLinearGradient>
#include <QPalette>
namespace s21 {
View::View(Controller *c, int argc, char **argv)
    : m_p_controller_(c), m_argc(argc), m_pp_argv(argv) {}

int View::startEventLoop() {
  QApplication app(m_argc, m_pp_argv);
  MainWidget window(nullptr, m_p_controller_);
  window.show();
  QLinearGradient gradient(0, 0, window.width(), window.height());
  gradient.setColorAt(0.2, "#666666");
  gradient.setColorAt(0.5, "#1b1b1b");

  QPalette pal;
  pal.setBrush(QPalette::Window, gradient);
  window.setPalette(pal);
  window.setAutoFillBackground(true);
  return app.exec();
}
}  // namespace s21
