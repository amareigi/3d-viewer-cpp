#ifndef S21_SRC_MODEL_MODEL_H_
#define S21_SRC_MODEL_MODEL_H_

#include <iostream>

#include "base_file_reader.h"
#include "file_reader.h"
#include "model_operation_result.h"
#include "normalization_parameters.h"
#include "scene.h"

namespace s21 {
class Model {
 private:
  BaseFileReader* m_p_file_reader_;
  Scene* m_p_scene_;

 public:
  Scene* GetScenePtr() { return m_p_scene_; }
  ModelOperationResult LoadFigureToScene(std::string path,
                                         NormalizationParameters param);
  Model();
  ~Model();
};
}  // namespace s21
#endif
