#ifndef SCENE_WIDGET_H
#define SCENE_WIDGET_H

#include <QDebug>
#include <QGridLayout>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <map>
#include <set>
#include <string>

#include "../controller/controller.h"

namespace s21 {
class SceneWidget : public QOpenGLWidget {
  Q_OBJECT
 private:
  GLfloat m_x_rotate_;
  GLfloat m_y_rotate_;
  QPoint m_mouse_position_;
  GLfloat m_x_center_;
  GLfloat m_y_center_;
  GLfloat m_z_center_;
  Figure* m_p_figure_;
  int m_call_list_num_;
  GLfloat m_rotate_angle_;
  GLfloat m_scale_;
  std::map<std::string, int> m_names_and_call_lists_map;
  std::set<std::string> m_figure_names_set;
  float m_background_red = 1.0;
  float m_background_green = 1.0;
  float m_background_blue = 1.0;
  float m_edge_red = 0.0;
  float m_edge_green = 0.0;
  float m_edge_blue = 0.0;
  float m_vertex_red = 0.0;
  float m_vertex_green = 0.0;
  float m_vertex_blue = 0.0;
  int m_width;
  int m_height;
  bool projection_type_parallel = true;
  bool projection_type_central = false;
  bool edge_type_solid = true;
  bool edge_type_dashed = false;
  bool vertex_type_no = true;
  bool vertex_type_circle = false;
  bool vertex_type_square = false;
  float discretization;
  float move_step = 1;
  float rotate_step = 1;
  float scale_step = 1;
  float edge_width;
  float vertex_size;
  void setupParallelProjection(int width, int height);
  void setupPerspectiveProjection(float zNear, float zFar);

 protected:
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
  void mousePressEvent(QMouseEvent* pe);
  void mouseMoveEvent(QMouseEvent* pe);
  GLuint createOpenGLCallList();
  void rotateFigure(GLfloat fSize1 = 0.0, GLfloat fSize2 = 0.0);

 public:
  SceneWidget(QWidget* pwgt = 0);

 public slots:
  void onCommandSended(const QString& str);
  void onSceneUpdated(Figure* figure_ptr);
  void onAngleChanged(float angle);
  void onColorChanged(const QString& color, float value);
  void onProjectionChanged(const QString& projection);
  void onVertexOrEdgeSizeChanged(const QString& name, float value);
  void onVertexTypeChanged(bool no, bool square, bool circle);
  void onEdgeTypeChanged(bool solid, bool dashed);
  void onMoveRotateScaleStepsChanged(float m_step, float r_step, float s_step);
};
}  // namespace s21
#endif  // SCENE_WIDGET_H
