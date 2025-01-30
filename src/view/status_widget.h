#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include <QGridLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

namespace s21 {
class StatusWidget : public QWidget {
  Q_OBJECT
 public:
  explicit StatusWidget(QWidget* parent = nullptr);

 private:
  QLineEdit* m_p_active_figure_path_;
  QLCDNumber* m_p_vertex_num_;
  QLCDNumber* m_p_edge_num_;
  QLCDNumber* m_p_loaded_figures_num_;
  QLCDNumber* m_p_active_figure_num_;
 signals:

 public slots:
  void onStatusUpdated(int v, int e, int f, int a, QString path);
};
}  // namespace s21
#endif  // STATUS_WIDGET_H
