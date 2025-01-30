#include "normalization_parameters.h"
namespace s21 {

NormalizationParameters::NormalizationParameters(double min, double max,
                                                 double dx_step, double dy_step,
                                                 double dz_step)
    : Min(min), Max(max), DxStep(dx_step), DyStep(dy_step), DzStep(dz_step) {}

double NormalizationParameters::GetMaxRange() {
  double res = std::abs(Min) + std::abs(Max);
  return res;
}

bool NormalizationParameters::NeedDiscritization() {
  bool res = true;
  if (!DxStep && !DyStep && !DzStep) res = false;
  return res;
}

}  // namespace s21
