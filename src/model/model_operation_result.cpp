#include "model_operation_result.h"

namespace s21 {

ModelOperationResult::ModelOperationResult() {
  m_error_message = "";
  m_success = 1;
}

std::string ModelOperationResult::GetErrorMessage() { return m_error_message; }

void ModelOperationResult::SetErrorMessage(std::string error) {
  m_error_message = error;
  m_success = 0;
}

bool ModelOperationResult::IsSuccess() { return m_success; }

}  // namespace s21
