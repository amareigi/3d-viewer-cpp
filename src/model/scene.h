#ifndef S21_SRC_MODEL_SCENE_H_
#define S21_SRC_MODEL_SCENE_H_

#include "figure.h"
namespace s21 {
class Scene {
 private:
  std::vector<Figure*> m_p_figures_;

 public:
  Scene(){};
  std::vector<Figure*>& GetFiguresRef();
  void AddNewFigure(Figure* figure);
  ~Scene();
};
}  // namespace s21
#endif
