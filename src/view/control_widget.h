#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
// для зажатия кнопок
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QStringList>
#include <QTimer>
#include <QValidator>

namespace s21 {
class ControlWidget : public QWidget {
  Q_OBJECT
 public:
  explicit ControlWidget(QWidget* parent = nullptr);

 private:
  QPushButton* m_p_ortho_button;
  QPushButton* m_p_isometric_button;

  QTimer* m_p_timer_;
  QString m_active_command_;
  QPushButton* createButton(const QString& str, bool checkable);

 private slots:
  void onButtonPressed();
  void onButtonReleased();
  void onTimerTimeout();

 signals:
  void commandSended(const QString&);
  void fileOpened(const QString&);
  void angleChanged(float);
  void SetScreenClicked();
  void SetGifClicked();
};
}  // namespace s21
#endif  // CONTROL_WIDGET_H
