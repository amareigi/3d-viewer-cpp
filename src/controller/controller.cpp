#include "controller.h"

namespace s21 {
ModelOperationResult Controller::LoadFigureToScene(
    std::string path, NormalizationParameters param) {
  return m_p_model_->LoadFigureToScene(path, param);
}

Scene *Controller::GetScenePtr() {
  return m_p_model_->GetScenePtr(/*num_figure*/);
}

Figure *Controller::GetFigurePtr(int figure_num) {
  return m_p_model_->GetScenePtr()->GetFiguresRef()[figure_num - 1];
}

int Controller::GetFigureVerticesNum(int figure_num) {
  return m_p_model_->GetScenePtr()
      ->GetFiguresRef()[figure_num - 1]
      ->GetVerticesRef()
      .size();
}

int Controller::GetFigureEdgesNum(int figure_num) {
  return m_p_model_->GetScenePtr()
      ->GetFiguresRef()[figure_num - 1]
      ->GetEdgesRef()
      .size();
}

int Controller::GetFiguresNum() {
  return m_p_model_->GetScenePtr()->GetFiguresRef().size();
}

std::string Controller::GetFigureFileName(int figure_num) {
  return m_p_model_->GetScenePtr()
      ->GetFiguresRef()[figure_num - 1]
      ->GetFileName();
}
}  // namespace s21
