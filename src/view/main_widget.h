#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QGridLayout>
#include <QWidget>

#include "control_widget.h"
#include "scene_widget.h"
#include "settings_widget.h"
#include "status_widget.h"

namespace s21 {
class MainWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MainWidget(QWidget* parent = nullptr, Controller* c = nullptr);

 private:
  Controller* m_p_controller_;
  ControlWidget* m_p_control_wgt_;
  SettingsWidget* m_p_settings_wgt_;
  StatusWidget* m_p_status_wgt_;
  SceneWidget* m_p_scene_wgt_;
  int m_active_figure_;
  float discret = 0.0;
  void updateSceneAndStatus();

 public slots:
  void onFileOpened(const QString& str);
  void onActiveFigureChanged(const QString& str);
  void onDiscretizationChanged(float value);
  void onSetScreenClicked();
  void onSetGifClicked();
  void captureFramesAndCreateGIF(const QString& outputFileName, int durationMs,
                                 int numFrames);
  void captureFrame(const QString& outputFilePath);
  void createGIF(const QString& inputDir, const QString& outputFileName,
                 int durationMs);

 signals:
  void sceneUpdated(Figure* figure_ptr);
  void statusUpdated(int v, int e, int f, int a, QString path);
};
}  // namespace s21
#endif  // MAIN_WIDGET_H
