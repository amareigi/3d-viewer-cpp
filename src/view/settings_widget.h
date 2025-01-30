#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QValidator>
#include <QWidget>
#include <vector>

namespace s21 {
class SettingsWidget : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsWidget(QWidget* parent = nullptr);

 private:
  QSettings* settings;
  bool projection_type_parallel;
  bool projection_type_central;
  bool edge_type_solid;
  bool edge_type_dashed;
  bool vertex_type_no;
  bool vertex_type_circle;
  bool vertex_type_square;
  float discretization;
  float move_step;
  float rotate_step;
  float scale_step;
  float edge_width;
  float vertex_size;
  float background_color_red;
  float background_color_green;
  float background_color_blue;
  float edge_color_red;
  float edge_color_green;
  float edge_color_blue;
  float vertex_color_red;
  float vertex_color_green;
  float vertex_color_blue;

  QPushButton* createButton(const QString& str, bool checkable);
  QLineEdit* createEditLine(const QString& name, const QString& text,
                            double bot, double top);
  QSlider* createSlider(const QString& name, int default_value);
  QLabel* createLabel(const QString& name);
  void saveSettings();
  void loadSettings();
  void sendSettings();

 signals:
  void colorChanged(const QString& color, float value);
  void vertexOrEdgeSizeChanged(const QString& name, float value);
  void projectionChanged(const QString& projection);
  void vertexTypeChanged(bool no, bool square, bool circle);
  void edgeTypeChanged(bool solid, bool dashed);
  void moveRotateScaleStepsChanged(float m_step, float r_step, float s_step);
  void discretizationChanged(float value);
 private slots:
  void onButtonPressed();
  void onSliderValueChanged(int val);
  void onEditingFinished();
};
}  // namespace s21
#endif  // SETTINGS_WIDGET_H
