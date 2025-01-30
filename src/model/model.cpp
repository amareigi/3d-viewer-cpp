#include "model.h"

namespace s21 {

ModelOperationResult Model::LoadFigureToScene(std::string path,
                                              NormalizationParameters param) {
  ModelOperationResult res;
  Figure* new_figure = nullptr;
  new_figure = m_p_file_reader_->ReadFigure(path, param);
  if (new_figure != nullptr) {
    m_p_scene_->AddNewFigure(new_figure);
  } else {
    res.SetErrorMessage("can`t open file");
  }
  return res;
}

Model::Model() {
  m_p_file_reader_ = new FileReader();
  m_p_scene_ = new Scene();
}

Model::~Model() {
  delete m_p_file_reader_;
  delete m_p_scene_;
}

}  // namespace s21
