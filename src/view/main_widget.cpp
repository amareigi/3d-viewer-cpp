#include "main_widget.h"

#include <QProcess>
#include <QThread>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace s21 {
MainWidget::MainWidget(QWidget *parent, Controller *c)
    : QWidget(parent), m_p_controller_(c) {
  m_p_control_wgt_ = new ControlWidget(this);
  m_p_settings_wgt_ = new SettingsWidget(this);
  m_p_status_wgt_ = new StatusWidget(this);
  m_p_scene_wgt_ = new SceneWidget(this);
  m_active_figure_ = 0;
  discret = 0.0;

  connect(m_p_control_wgt_, SIGNAL(commandSended(const QString &)),
          m_p_scene_wgt_, SLOT(onCommandSended(const QString &)));
  // change active figure
  connect(m_p_control_wgt_, SIGNAL(commandSended(const QString &)), this,
          SLOT(onActiveFigureChanged(const QString &)));
  // open file
  connect(m_p_control_wgt_, SIGNAL(fileOpened(const QString &)), this,
          SLOT(onFileOpened(const QString &)));
  // discretization changed
  connect(m_p_settings_wgt_, SIGNAL(discretizationChanged(float)), this,
          SLOT(onDiscretizationChanged(float)));
  // color to scene
  connect(m_p_settings_wgt_, SIGNAL(colorChanged(const QString &, float)),
          m_p_scene_wgt_, SLOT(onColorChanged(const QString &, float)));
  // projection to scene
  connect(m_p_settings_wgt_, SIGNAL(projectionChanged(const QString &)),
          m_p_scene_wgt_, SLOT(onProjectionChanged(const QString &)));
  // vertex and edge sizes to scene
  connect(m_p_settings_wgt_,
          SIGNAL(vertexOrEdgeSizeChanged(const QString &, float)),
          m_p_scene_wgt_,
          SLOT(onVertexOrEdgeSizeChanged(const QString &, float)));
  // vertex type to scene
  connect(m_p_settings_wgt_, SIGNAL(vertexTypeChanged(bool, bool, bool)),
          m_p_scene_wgt_, SLOT(onVertexTypeChanged(bool, bool, bool)));
  // edge type to scene
  connect(m_p_settings_wgt_, SIGNAL(edgeTypeChanged(bool, bool)),
          m_p_scene_wgt_, SLOT(onEdgeTypeChanged(bool, bool)));
  // steps to scene
  connect(m_p_settings_wgt_,
          SIGNAL(moveRotateScaleStepsChanged(float, float, float)),
          m_p_scene_wgt_,
          SLOT(onMoveRotateScaleStepsChanged(float, float, float)));
  // data to scene
  connect(this, SIGNAL(sceneUpdated(Figure *)), m_p_scene_wgt_,
          SLOT(onSceneUpdated(Figure *)));
  // data to status
  connect(this, SIGNAL(statusUpdated(int, int, int, int, QString)),
          m_p_status_wgt_, SLOT(onStatusUpdated(int, int, int, int, QString)));

  connect(m_p_control_wgt_, SIGNAL(SetScreenClicked()), this,
          SLOT(onSetScreenClicked()));
  connect(m_p_control_wgt_, SIGNAL(SetGifClicked()), this,
          SLOT(onSetGifClicked()));

  QVBoxLayout *vboxLayout = new QVBoxLayout();
  vboxLayout->addWidget(m_p_control_wgt_);
  vboxLayout->addWidget(m_p_settings_wgt_);
  vboxLayout->addWidget(m_p_status_wgt_);

  QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
  layout->addLayout(vboxLayout, 1);
  layout->addWidget(m_p_scene_wgt_, 5);

  setLayout(layout);

  setWindowTitle("3D_Viewer");
  resize(400, 400);
}

void MainWidget::updateSceneAndStatus() {
  emit sceneUpdated(m_p_controller_->GetFigurePtr(m_active_figure_));

  emit statusUpdated(m_p_controller_->GetFigureVerticesNum(m_active_figure_),
                     m_p_controller_->GetFigureEdgesNum(m_active_figure_),
                     m_p_controller_->GetFiguresNum(), m_active_figure_,
                     QString::fromStdString(
                         m_p_controller_->GetFigureFileName(m_active_figure_)));
}

void MainWidget::onFileOpened(const QString &str) {
  ModelOperationResult res;
  res = m_p_controller_->LoadFigureToScene(
      str.toStdString(),
      NormalizationParameters(1, -1, discret, discret, discret));
  if (res.IsSuccess()) {
    m_active_figure_++;
    updateSceneAndStatus();
  }
}

void MainWidget::onActiveFigureChanged(const QString &str) {
  if (str == "Next Figure" &&
      m_active_figure_ < m_p_controller_->GetFiguresNum()) {
    m_active_figure_++;
    updateSceneAndStatus();
  }
  if (str == "Previous Figure" && m_active_figure_ > 1) {
    m_active_figure_--;
    updateSceneAndStatus();
  }
}

void MainWidget::onDiscretizationChanged(float value) { discret = value; }

void MainWidget::onSetScreenClicked() {
  // устанавливаем фильтры директориии
  QStringList filter;
  filter << "Bitmap Files (*.bmp)"
         << "JPEG Files (*.jpg *.jpeg)";
  QString filterString = filter.join(";;");
  // дефолтное название для скриншота
  QString defaultName = "Screenshot_";

  // путь до файла
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранить изображение",
                                                  defaultName, filterString);
  // если не указали расширение, то сохраняем в PNG и JPEG
  if ((!fileName.endsWith("." + QString("jpg"), Qt::CaseInsensitive) &&
       !fileName.endsWith("." + QString("jpeg"), Qt::CaseInsensitive)) &&
      !fileName.endsWith("." + QString("bmp"))) {
    // дублируем путь, добавляем расширение, захватываем экран для BMP
    QString filenNameTmp = fileName;
    filenNameTmp += "." + QString("bmp");
    QImage picBmp = m_p_scene_wgt_->grabFramebuffer();
    picBmp.save(filenNameTmp, "BMP");
    // добавляем расширение, захватываем экран для JPEG
    fileName += "." + QString("jpg");
    QImage picJpg = m_p_scene_wgt_->grabFramebuffer();
    picJpg.save(fileName, "JPEG");
  } else {
    // если указано расширение
    QImage pic = m_p_scene_wgt_->grabFramebuffer();
    pic.save(fileName);
  }
}

void MainWidget::onSetGifClicked() {
  std::string img_name = "Animation_";
  img_name.append(".gif");
  QString gifFileName = QFileDialog::getSaveFileName(
      this, tr("Open Address book"), QString::fromStdString(img_name),
      tr("Address book (*.gif)"));
  // Set the total duration of the GIF in milliseconds
  int gifDurationMs = 5000;
  // Set the number of frames to capture
  int numFrames = 50;

  captureFramesAndCreateGIF(gifFileName, gifDurationMs, numFrames);
}

void MainWidget::captureFramesAndCreateGIF(const QString &outputFileName,
                                           int durationMs, int numFrames) {
  QString tempDir = QCoreApplication::applicationDirPath() + "/frames";
  QDir().mkpath(tempDir);

  for (int i = 0; i < numFrames; ++i) {
    QString frameFilePath = tempDir + QString("/frame_%1.png").arg(i);
    captureFrame(frameFilePath);
    QCoreApplication::processEvents();  // Allow the application to process
                                        // events
    QThread::msleep(durationMs / numFrames);
  }

  createGIF(tempDir, outputFileName, durationMs);

  // Clean up temporary frames
  QDir(tempDir).removeRecursively();
}

void MainWidget::captureFrame(const QString &outputFilePath) {
  unsigned int width = m_p_scene_wgt_->width();
  unsigned int height = m_p_scene_wgt_->height();

  unsigned char *output = new unsigned char[width * height * 4];
  glReadPixels(612, 10, width, height, GL_BGRA, GL_UNSIGNED_BYTE, output);

  QImage image(output, width, height, QImage::Format_RGB32);
  image = image.mirrored();  // Flip the image vertically if needed

  image.save(outputFilePath);

  delete[] output;
}

void MainWidget::createGIF(const QString &inputDir,
                           const QString &outputFileName, int durationMs) {
  QStringList arguments;
  arguments << "-framerate"
            << "10"  // Set the frame rate (adjust as needed)
            << "-i" << inputDir + "/frame_%d.png"
            << "-t"
            << QString::number(durationMs)  // Duration per frame in seconds
            << "-y" << outputFileName;

  QProcess process;
  process.start("ffmpeg", arguments);
  process.waitForFinished();

  qDebug() << "GIF file created: " << outputFileName;
}
}  // namespace s21
