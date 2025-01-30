#ifndef S21_SRC_MODEL_MODEL_OPERATION_RESULT_H_
#define S21_SRC_MODEL_MODEL_OPERATION_RESULT_H_

#include <string>

namespace s21 {
class ModelOperationResult {
 private:
  std::string m_error_message;
  bool m_success;

 public:
  ModelOperationResult();
  std::string GetErrorMessage();
  void SetErrorMessage(std::string error);
  bool IsSuccess();
};
}  // namespace s21
#endif
