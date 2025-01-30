#ifndef S21_SRC_MODEL_BASE_FILE_READER_H_
#define S21_SRC_MODEL_BASE_FILE_READER_H_

#include <string>

#include "normalization_parameters.h"
#include "scene.h"
namespace s21 {
class BaseFileReader {
 public:
  virtual s21::Figure* ReadFigure(std::string path,
                                  NormalizationParameters param) = 0;
  virtual ~BaseFileReader() = default;
};
}  // namespace s21
#endif
