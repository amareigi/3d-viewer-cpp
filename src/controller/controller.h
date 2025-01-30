#ifndef S21_SRC_CONTROLLER_CONTROLLER_H_
#define S21_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"
namespace s21 {
class Controller {
 private:
  Model* m_p_model_;

 public:
  Controller(Model* model) : m_p_model_(model) {}

  ModelOperationResult LoadFigureToScene(std::string path,
                                         NormalizationParameters param);

  Scene* GetScenePtr(/*int num_figure*/);

  Figure* GetFigurePtr(int figure_num);

  int GetFigureVerticesNum(int figure_num);
  int GetFigureEdgesNum(int figure_num);
  int GetFiguresNum();
  std::string GetFigureFileName(int figure_num);
};
}  // namespace s21
#endif
