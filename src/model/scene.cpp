#include "scene.h"

namespace s21 {

std::vector<Figure *> &Scene::GetFiguresRef() { return m_p_figures_; }

void Scene::AddNewFigure(Figure *figure) { m_p_figures_.push_back(figure); }

Scene::~Scene() {
  for (size_t i = 0; i < m_p_figures_.size(); ++i)
    if (m_p_figures_[i] != nullptr) delete m_p_figures_[i];
}

}  // namespace s21
