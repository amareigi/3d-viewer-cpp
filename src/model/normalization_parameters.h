#ifndef S21_SRC_MODEL_NORMALIZATION_PARAMETERS_H_
#define S21_SRC_MODEL_NORMALIZATION_PARAMETERS_H_

#include <cmath>  // abs

namespace s21 {
class NormalizationParameters {
 public:
  double Min;
  double Max;
  double DxStep;
  double DyStep;
  double DzStep;
  NormalizationParameters()
      : Min(0.0), Max(0.0), DxStep(0.0), DyStep(0.0), DzStep(0.0) {}

  NormalizationParameters(double min, double max, double dx_step = 0.0,
                          double dy_step = 0.0, double dz_step = 0.0);

  double GetMaxRange();

  bool NeedDiscritization();
};
}  // namespace s21
#endif
