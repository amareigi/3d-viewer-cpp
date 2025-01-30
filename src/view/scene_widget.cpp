#include "scene_widget.h"

#include <QDebug>

namespace s21 {
SceneWidget::SceneWidget(QWidget* pwgt)
    : QOpenGLWidget(pwgt),
      m_x_rotate_(0),
      m_y_rotate_(0),
      m_x_center_(0.0),
      m_y_center_(0.0),
      m_z_center_(-2.0),
      m_p_figure_(nullptr),
      m_call_list_num_(0),
      m_rotate_angle_(10.0),
      m_scale_(1.0) {
  edge_width = 0.1;
  vertex_size = 0.1;
  QGridLayout* ptopLayout = new QGridLayout;
  this->setMinimumSize(400, 400);
  setLayout(ptopLayout);
}

void SceneWidget::onCommandSended(const QString& str) {
  if (str == "Rotate Up") rotateFigure(-rotate_step, 0);
  if (str == "Rotate Down") rotateFigure(rotate_step, 0);
  if (str == "Rotate Left") rotateFigure(0, -rotate_step);
  if (str == "Rotate Right") rotateFigure(0, rotate_step);
  if (str == "Zoom+") {
    m_scale_ += scale_step;
  }
  if (str == "Zoom-") {
    if (m_scale_ > 0.1) m_scale_ -= scale_step;
  }
  if (str == "Move Up") m_y_center_ += move_step;
  if (str == "Move Down") m_y_center_ -= move_step;
  if (str == "Move Left") m_x_center_ -= move_step;
  if (str == "Move Right") m_x_center_ += move_step;
  if (str == "Reset Scene") {
    m_x_center_ = 0;
    m_y_center_ = 0;
    m_z_center_ = -2.0;
    m_x_rotate_ = 0;
    m_y_rotate_ = 0;
    m_scale_ = 1;
    m_background_red = 1.0;
    m_background_green = 1.0;
    m_background_blue = 1.0;
    m_edge_red = 0.0;
    m_edge_green = 0.0;
    m_edge_blue = 0.0;
  }
  update();
}

void SceneWidget::onSceneUpdated(Figure* figure_ptr) {
  m_p_figure_ = figure_ptr;
  std::string file_name = m_p_figure_->GetFileName();
  // вставляю новое имя в сет
  auto it = m_figure_names_set.emplace(file_name);
  // если оно новое, то it.second true
  if (it.second) {
    m_call_list_num_ = createOpenGLCallList();
    // запоминаю имя в связке с номером calllist
    m_names_and_call_lists_map.emplace(file_name, m_call_list_num_);
  } else {
    // если имя уже было, то ищу номер calllista для этого имени
    auto map_it = m_names_and_call_lists_map.find(file_name);
    m_call_list_num_ = map_it->second;
  }
  update();
}

GLuint SceneWidget::createOpenGLCallList() {
  glLineWidth(edge_width);
  if (edge_type_dashed) {
    glLineStipple(1, 0x1111);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glBegin(GL_LINES);
  glColor3f(m_edge_red, m_edge_green, m_edge_blue);
  for (size_t i = 0; i < m_p_figure_->GetEdgesRef().size(); i++) {
    ThreeDPoint begin =
        m_p_figure_->GetEdgesRef()[i].GetBegin().GetPositionRef();
    ThreeDPoint end = m_p_figure_->GetEdgesRef()[i].GetEnd().GetPositionRef();
    glVertex3d(begin.X, begin.Y, begin.Z);
    glVertex3d(end.X, end.Y, end.Z);
  }
  glEnd();
  if (!vertex_type_no) {
    glPointSize(vertex_size);
    if (vertex_type_circle) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glBegin(GL_POINTS);
    glColor3f(m_vertex_red, m_vertex_green, m_vertex_blue);
    for (size_t i = 0; i < m_p_figure_->GetEdgesRef().size(); i++) {
      ThreeDPoint begin =
          m_p_figure_->GetEdgesRef()[i].GetBegin().GetPositionRef();
      ThreeDPoint end = m_p_figure_->GetEdgesRef()[i].GetEnd().GetPositionRef();
      glVertex3d(begin.X, begin.Y, begin.Z);
      glVertex3d(end.X, end.Y, end.Z);
    }
    glEnd();
  }
  return 1;
}
void SceneWidget::onAngleChanged(float angle) { m_rotate_angle_ = angle; }

void SceneWidget::onColorChanged(const QString& color, float value) {
  if (color == "background_red") m_background_red = value;
  if (color == "background_green") m_background_green = value;
  if (color == "background_blue") m_background_blue = value;
  if (color == "edge_red") m_edge_red = value;
  if (color == "edge_green") m_edge_green = value;
  if (color == "edge_blue") m_edge_blue = value;
  if (color == "vertex_red") m_vertex_red = value;
  if (color == "vertex_green") m_vertex_green = value;
  if (color == "vertex_blue") m_vertex_blue = value;
  update();
}

void SceneWidget::onProjectionChanged(const QString& projection) {
  if (projection == "Parallel projection") {
    projection_type_parallel = true;
    projection_type_central = false;
  }
  if (projection == "Central projection") {
    projection_type_central = true;
    projection_type_parallel = false;
  }
  update();
}

void SceneWidget::onVertexOrEdgeSizeChanged(const QString& name, float value) {
  if (name == "Edge width") {
    edge_width = value;
  }
  if (name == "Vertex size") {
    vertex_size = value;
  }
  update();
}

void SceneWidget::onVertexTypeChanged(bool no, bool square, bool circle) {
  vertex_type_no = no;
  vertex_type_circle = circle;
  vertex_type_square = square;
  update();
}

void SceneWidget::onEdgeTypeChanged(bool solid, bool dashed) {
  edge_type_solid = solid;
  edge_type_dashed = dashed;
  update();
}

void SceneWidget::onMoveRotateScaleStepsChanged(float m_step, float r_step,
                                                float s_step) {
  move_step = m_step;
  rotate_step = r_step;
  scale_step = s_step;
}

void SceneWidget::setupParallelProjection(int width, int height) {
  glMatrixMode(GL_PROJECTION);  // Переключаемся на матрицу проекции
  glLoadIdentity();  // Сбрасываем текущую матрицу

  // Определяем видимую область ортографической проекции
  float aspect = static_cast<float>(width) / height;
  float left = -10.0f * aspect;
  float right = 10.0f * aspect;
  float bottom = -10.0f;
  float top = 10.0f;
  float near = -100.0f;
  float far = 100.0f;

  glOrtho(left, right, bottom, top, near, far);

  glMatrixMode(GL_MODELVIEW);  // Возвращаемся к матрице модели/вида
  glLoadIdentity();  // Сбрасываем матрицу модели/вида
}

void SceneWidget::setupPerspectiveProjection(float zNear, float zFar) {
  glMatrixMode(GL_PROJECTION);  // Переключаемся на матрицу проекции
  glLoadIdentity();  // Сбрасываем текущую матрицу

  // Устанавливаем перспективную проекцию
  glFrustum(-1.0, 1.0, -1.0, 1.0, zNear, zFar);

  glMatrixMode(GL_MODELVIEW);  // Возвращаемся к матрице модели/вида
  glLoadIdentity();  // Сбрасываем матрицу модели/вида
}

void SceneWidget::initializeGL() {
  QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
  pFunc->glClearColor(m_background_red, m_background_green, m_background_blue,
                      1.0f);
  pFunc->glEnable(GL_DEPTH_TEST);
  pFunc->glDepthFunc(GL_LESS);
  pFunc->glEnable(GL_CULL_FACE);
  pFunc->glCullFace(GL_BACK);
  pFunc->glFrontFace(GL_CW);
  pFunc->glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
}

void SceneWidget::resizeGL(int width, int height) {
  glClearColor(m_background_red, m_background_green, m_background_blue, 1.0f);
  m_width = width;
  m_height = height;
  glViewport(0, 0, width, height);  // Устанавливаем область вывода

  // Настраиваем перспективу
  if (projection_type_parallel)
    setupParallelProjection(width, height);
  else
    setupPerspectiveProjection(0.1f, 5.0f);
}

void SceneWidget::paintGL() {
  glClearColor(m_background_red, m_background_green, m_background_blue, 1.0f);
  if (projection_type_parallel)
    setupParallelProjection(m_width, m_height);
  else
    setupPerspectiveProjection(0.1f, 5.0f);

  if (m_p_figure_ != nullptr) {
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // чтобы от старого кадра ничего не осталось

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(m_x_center_, m_y_center_,
                 m_z_center_);  // положение центра по осям
    glScalef(m_scale_, m_scale_, m_scale_);  // массштаб
    glRotatef(m_x_rotate_, 1.0, 0.0,
              0.0);  // первый параметр угл на который изменить
    glRotatef(m_y_rotate_, 0.0, 1.0, 0.0);
    createOpenGLCallList();
  }
}

void SceneWidget::mousePressEvent(QMouseEvent* mouse_event_ptr) {
  m_mouse_position_ = mouse_event_ptr->pos();
}

void SceneWidget::mouseMoveEvent(QMouseEvent* mouse_event_ptr) {
  rotateFigure(mouse_event_ptr->y() - m_mouse_position_.y(),
               mouse_event_ptr->x() - m_mouse_position_.x());
  update();
  m_mouse_position_ = mouse_event_ptr->pos();
}

void SceneWidget::rotateFigure(GLfloat fSize1, GLfloat fSize2) {
  m_x_rotate_ += 180 * (GLfloat)(fSize1) / height();
  m_y_rotate_ += 180 * (GLfloat)(fSize2) / width();
}
}  // namespace s21
