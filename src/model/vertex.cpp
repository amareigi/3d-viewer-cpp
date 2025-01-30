#include "vertex.h"

namespace s21 {

Vertex::Vertex(double x, double y, double z) : m_position_(x, y, z) {}

ThreeDPoint &Vertex::GetPositionRef() { return m_position_; }
}  // namespace s21
