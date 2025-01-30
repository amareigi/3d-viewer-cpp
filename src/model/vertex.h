#ifndef S21_SRC_MODEL_VERTEX_H_
#define S21_SRC_MODEL_VERTEX_H_

#include <iostream>

#include "three_d_point.h"

namespace s21 {
class Vertex {
 private:
  ThreeDPoint m_position_;

 public:
  Vertex() {}
  Vertex(double x, double y, double z);
  ThreeDPoint& GetPositionRef();
};
}  // namespace s21
#endif
