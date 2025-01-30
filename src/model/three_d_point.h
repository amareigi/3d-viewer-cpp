#ifndef S21_SRC_MODEL_THREE_D_POINT_H_
#define S21_SRC_MODEL_THREE_D_POINT_H_

#include <cmath>

namespace s21 {
class ThreeDPoint {
 public:
  double X;
  double Y;
  double Z;
  ThreeDPoint() : X(0.0), Y(0.0), Z(0.0) {}
  ThreeDPoint(double x, double y, double z) : X(x), Y(y), Z(z) {}
};
}  // namespace s21
#endif
