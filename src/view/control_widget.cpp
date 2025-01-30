#include "control_widget.h"

#include <QStyleFactory>

namespace s21 {
ControlWidget::ControlWidget(QWidget* parent) : QWidget(parent) {
  // для зажатия кнопок
  m_p_timer_ = new QTimer(this);
  m_p_timer_->setInterval(50);  // интервал зажатия кнопки в миллисекундах
  connect(m_p_timer_, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

  m_active_command_ = "";

  QString aButtons[4][4] = {
      {"Open File", "Reset Scene", "Next Figure", "Previous Figure"},
      {"Move Up", "Move Down", "Move Left", "Move Right"},
      {"Rotate Up", "Rotate Down", "Rotate Left", "Rotate Right"},
      {"Zoom+", "Zoom-", "Screenshot", "Gif"}};

  // Layout setup
  QGridLayout* layout = new QGridLayout;
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      layout->addWidget(createButton(aButtons[i][j], false), i, j);

  setLayout(layout);
}

QPushButton* ControlWidget::createButton(const QString& str, bool checkable) {
  QPushButton* button = new QPushButton(str, this);
  button->setMinimumSize(140, 40);
  if (checkable) button->setCheckable(true);
  button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // чтобы кнопки растягивались
  connect(button, SIGNAL(pressed()), this, SLOT(onButtonPressed()));
  connect(button, SIGNAL(released()), this, SLOT(onButtonReleased()));
  return button;
}

void ControlWidget::onButtonPressed() {
  QString str = ((QPushButton*)sender())->text();
  if (str == "Open File") {
    QStringList file_names = QFileDialog::getOpenFileNames(this);
    for (QStringList::iterator i = file_names.begin(); i != file_names.end();
         ++i) {
      emit fileOpened(*i);
    }
  } else if (str == "Screenshot") {
    emit SetScreenClicked();
  } else if (str == "Gif") {
    emit SetGifClicked();
  } else {
    m_active_command_ = str;
    m_p_timer_->start();  // Запускаем таймер, если кнопка зажата
  }
}

void ControlWidget::onTimerTimeout() {
  if (!m_active_command_.isEmpty()) {
    emit commandSended(
        m_active_command_);  // Отправляем сигнал с текущим действием
  }
}

void ControlWidget::onButtonReleased() {
  m_p_timer_->stop();         // Останавливаем таймер
  m_active_command_.clear();  // Сбрасываем активное действие
}
}  // namespace s21
