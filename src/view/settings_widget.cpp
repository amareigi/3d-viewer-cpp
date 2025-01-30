#include "settings_widget.h"

namespace s21 {
SettingsWidget::SettingsWidget(QWidget* parent) : QWidget{parent} {
  settings = new QSettings("School21", "3D_Viewer");
  projection_type_parallel = true;
  projection_type_central = false;
  edge_type_solid = true;
  edge_type_dashed = false;
  vertex_type_no = true;
  vertex_type_circle = false;
  vertex_type_square = false;
  discretization = 0.0;
  move_step = 1.0;
  rotate_step = 1.0;
  scale_step = 1.0;
  edge_width = 1.0;
  vertex_size = 1.0;
  background_color_red = 1.0;
  background_color_green = 1.0;
  background_color_blue = 1.0;
  edge_color_red = 0.0;
  edge_color_green = 0.0;
  edge_color_blue = 0.0;
  vertex_color_red = 0.0;
  vertex_color_green = 0.0;
  vertex_color_blue = 0.0;

  QGridLayout* first_layout = new QGridLayout;
  QString Buttons[2][4] = {
      {"Parallel projection", "Vertex circle", "Edge solid", "Save settings"},
      {"Central projection", "Vertex square", "Edge dashed", "Load settings"}};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      first_layout->addWidget(createButton(Buttons[i][j], false), i, j);
  first_layout->addWidget(createLabel("Vertex size"), 2, 0);
  first_layout->addWidget(createSlider("Vertex size", 0), 2, 1);
  first_layout->addWidget(createLabel("Edge width"), 2, 2);
  first_layout->addWidget(createSlider("Edge width", 0), 2, 3);

  QGridLayout* second_layout = new QGridLayout;
  second_layout->addWidget(
      createEditLine("Discretization step", "Discretization step(0.0-1.0)", 0.0,
                     1.0),
      0, 0, 1, 3);
  second_layout->addWidget(
      createEditLine("Move step", "Move step (0.0-100.0)", 0.0, 100.0), 0, 3, 1,
      3);
  second_layout->addWidget(
      createEditLine("Rotate step", "Rotate step (0.0-100.0)", 0.0, 100.0), 1,
      0, 1, 3);
  second_layout->addWidget(
      createEditLine("Scale step", "Scale step (0.0-1.0)", 0.0, 1.0), 1, 3, 1,
      3);

  second_layout->addWidget(createLabel("Background RGB"), 2, 0, 1, 2);
  second_layout->addWidget(createSlider("background_red", 1000), 3, 0, 1, 2);
  second_layout->addWidget(createSlider("background_green", 1000), 4, 0, 1, 2);
  second_layout->addWidget(createSlider("background_blue", 1000), 5, 0, 1, 2);
  second_layout->addWidget(createLabel("Edge RGB"), 2, 2, 1, 2);
  second_layout->addWidget(createSlider("edge_red", 0), 3, 2, 1, 2);
  second_layout->addWidget(createSlider("edge_green", 0), 4, 2, 1, 2);
  second_layout->addWidget(createSlider("edge_blue", 0), 5, 2, 1, 2);
  second_layout->addWidget(createLabel("Vertex RGB"), 2, 4, 1, 2);
  second_layout->addWidget(createSlider("vertex_red", 0), 3, 4, 1, 2);
  second_layout->addWidget(createSlider("vertex_green", 0), 4, 4, 1, 2);
  second_layout->addWidget(createSlider("vertex_blue", 0), 5, 4, 1, 2);

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addLayout(first_layout);
  layout->addLayout(second_layout);
  setLayout(layout);
}

QPushButton* SettingsWidget::createButton(const QString& str, bool checkable) {
  QPushButton* button = new QPushButton(str, this);
  button->setMinimumSize(140, 40);
  if (checkable) button->setCheckable(true);
  button->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);  // чтобы кнопки растягивались
  connect(button, SIGNAL(pressed()), this, SLOT(onButtonPressed()));
  return button;
}

QLineEdit* SettingsWidget::createEditLine(const QString& name,
                                          const QString& text, double bot,
                                          double top) {
  QLineEdit* line_edit = new QLineEdit(this);
  line_edit->setObjectName(name);
  line_edit->setPlaceholderText(text);
  QDoubleValidator* validator = new QDoubleValidator(bot, top, 7, this);
  line_edit->setValidator(validator);
  connect(line_edit, SIGNAL(editingFinished()), this,
          SLOT(onEditingFinished()));
  return line_edit;
}

QSlider* SettingsWidget::createSlider(const QString& name, int default_value) {
  QSlider* slider = new QSlider(Qt::Horizontal, this);
  slider->setObjectName(name);
  slider->setRange(0, 1000);
  slider->setValue(default_value);
  slider->setSingleStep(1);
  connect(slider, SIGNAL(valueChanged(int)), this,
          SLOT(onSliderValueChanged(int)));
  return slider;
}

QLabel* SettingsWidget::createLabel(const QString& name) {
  QLabel* label = new QLabel;
  label->setText(name);
  label->setAlignment(Qt::AlignCenter);
  return label;
}

void SettingsWidget::saveSettings() {
  settings->setValue("projection_type_parallel", projection_type_parallel);
  settings->setValue("projection_type_central", projection_type_central);
  settings->setValue("edge_type_solid", edge_type_solid);
  settings->setValue("edge_type_dashed", edge_type_dashed);
  settings->setValue("vertex_type_no", vertex_type_no);
  settings->setValue("vertex_type_circle", vertex_type_circle);
  settings->setValue("vertex_type_square", vertex_type_square);
  settings->setValue("discretization", discretization);
  settings->setValue("move_step", move_step);
  settings->setValue("rotate_step", rotate_step);
  settings->setValue("scale_step", scale_step);
  settings->setValue("edge_width", edge_width);
  settings->setValue("vertex_size", vertex_size);
  settings->setValue("background_color_red", background_color_red);
  settings->setValue("background_color_green", background_color_green);
  settings->setValue("background_color_blue", background_color_blue);
  settings->setValue("edge_color_red", edge_color_red);
  settings->setValue("edge_color_green", edge_color_green);
  settings->setValue("edge_color_blue", edge_color_blue);
  settings->setValue("vertex_color_red", vertex_color_red);
  settings->setValue("vertex_color_green", vertex_color_green);
  settings->setValue("vertex_color_blue", vertex_color_blue);
}

void SettingsWidget::loadSettings() {
  projection_type_parallel =
      settings->value("projection_type_parallel", true).toBool();
  projection_type_central =
      settings->value("projection_type_central", false).toBool();
  edge_type_solid = settings->value("edge_type_solid", true).toBool();
  edge_type_dashed = settings->value("edge_type_dashed", false).toBool();
  vertex_type_no = settings->value("vertex_type_no", true).toBool();
  vertex_type_circle = settings->value("vertex_type_circle", false).toBool();
  vertex_type_square = settings->value("vertex_type_square", false).toBool();
  discretization = settings->value("discretization", 0.0).toFloat();
  move_step = settings->value("move_step", 1.0).toFloat();
  rotate_step = settings->value("rotate_step", 1.0).toFloat();
  scale_step = settings->value("scale_step", 1.0).toFloat();
  edge_width = settings->value("edge_width", 1).toFloat();
  vertex_size = settings->value("vertex_size", 1).toFloat();
  background_color_red = settings->value("background_color_red", 1.0).toFloat();
  background_color_green =
      settings->value("background_color_green", 1.0).toFloat();
  background_color_blue =
      settings->value("background_color_blue", 1.0).toFloat();
  edge_color_red = settings->value("edge_color_red", 0.0).toFloat();
  edge_color_green = settings->value("edge_color_green", 0.0).toFloat();
  edge_color_blue = settings->value("edge_color_blue", 0.0).toFloat();
  vertex_color_red = settings->value("vertex_color_red", 0.0).toFloat();
  vertex_color_green = settings->value("vertex_color_green", 0.0).toFloat();
  vertex_color_blue = settings->value("vertex_color_blue", 0.0).toFloat();
}

void SettingsWidget::sendSettings() {
  // send projection settings
  if (projection_type_parallel)
    emit projectionChanged("Parralel projection");
  else
    emit projectionChanged("Central projection");

  // send edge type settings
  emit edgeTypeChanged(edge_type_solid, edge_type_dashed);

  // send vertex type settings
  emit vertexTypeChanged(vertex_type_no, vertex_type_square,
                         vertex_type_circle);

  // send edge and vertex size settings
  emit vertexOrEdgeSizeChanged("Edge width", edge_width);
  emit vertexOrEdgeSizeChanged("Vertex size", vertex_size);

  // send editlines settings
  emit discretizationChanged(discretization);
  emit moveRotateScaleStepsChanged(move_step, rotate_step, scale_step);

  // send color settings
  emit colorChanged("background_red", background_color_red);
  emit colorChanged("background_green", background_color_green);
  emit colorChanged("background_blue", background_color_blue);
  emit colorChanged("edge_red", edge_color_red);
  emit colorChanged("edge_green", edge_color_green);
  emit colorChanged("edge_blue", edge_color_blue);
  emit colorChanged("vertex_red", vertex_color_red);
  emit colorChanged("vertex_green", vertex_color_green);
  emit colorChanged("vertex_blue", vertex_color_blue);
}

void SettingsWidget::onButtonPressed() {
  QString name = ((QPushButton*)sender())->text();
  if (name == "Parallel projection") {
    projection_type_parallel = true;
    projection_type_central = false;
    projectionChanged(name);
  }
  if (name == "Central projection") {
    projection_type_central = true;
    projection_type_parallel = false;
    projectionChanged(name);
  }
  if (name == "Vertex circle") {
    if (vertex_type_circle) {
      vertex_type_no = true;
      vertex_type_circle = false;
      vertex_type_square = false;
    } else {
      vertex_type_circle = true;
      vertex_type_no = false;
      vertex_type_square = false;
    }
    emit vertexTypeChanged(vertex_type_no, vertex_type_square,
                           vertex_type_circle);
  }
  if (name == "Vertex square") {
    if (vertex_type_square) {
      vertex_type_no = true;
      vertex_type_circle = false;
      vertex_type_square = false;
    } else {
      vertex_type_square = true;
      vertex_type_circle = false;
      vertex_type_no = false;
    }
    emit vertexTypeChanged(vertex_type_no, vertex_type_square,
                           vertex_type_circle);
  }
  if (name == "Edge solid") {
    edge_type_solid = true;
    edge_type_dashed = false;
    emit edgeTypeChanged(edge_type_solid, edge_type_dashed);
  }
  if (name == "Edge dashed") {
    edge_type_dashed = true;
    edge_type_solid = false;
    emit edgeTypeChanged(edge_type_solid, edge_type_dashed);
  }
  if (name == "Save settings") {
    saveSettings();
  }
  if (name == "Load settings") {
    loadSettings();
    sendSettings();
  }
}

void SettingsWidget::onEditingFinished() {
  QString name = ((QLineEdit*)sender())->objectName();
  if (name == "Discretization step") {
    discretization = ((QLineEdit*)sender())->text().toFloat();
    emit discretizationChanged(((QLineEdit*)sender())->text().toFloat());
  } else {
    if (name == "Move step")
      move_step = ((QLineEdit*)sender())->text().toFloat();
    if (name == "Rotate step")
      rotate_step = ((QLineEdit*)sender())->text().toFloat();
    if (name == "Scale step")
      scale_step = ((QLineEdit*)sender())->text().toFloat();
    emit moveRotateScaleStepsChanged(move_step, rotate_step, scale_step);
  }
}

void SettingsWidget::onSliderValueChanged(int val) {
  QString name = ((QSlider*)sender())->objectName();
  float value = (float)val / 1000.0;
  if (name == "background_red") background_color_red = value;
  if (name == "background_green") background_color_green = value;
  if (name == "background_blue") background_color_blue = value;
  if (name == "edge_red") edge_color_red = value;
  if (name == "edge_green") edge_color_green = value;
  if (name == "edge_blue") edge_color_blue = value;
  if (name == "vertex_red") vertex_color_red = value;
  if (name == "vertex_green") vertex_color_green = value;
  if (name == "vertex_blue") vertex_color_blue = value;
  if (name != "Vertex size" && name != "Edge width")
    emit colorChanged(name, value);

  if (name == "Edge width") {
    value = (float)val / 100.0;
    edge_width = value;
    emit vertexOrEdgeSizeChanged(name, value);
  }
  if (name == "Vertex size") {
    value = (float)val / 10.0;
    vertex_size = value;
    emit vertexOrEdgeSizeChanged(name, value);
  }
}
}  // namespace s21
