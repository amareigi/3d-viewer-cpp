#ifndef S21_SRC_MODEL_EDGE_H_
#define S21_SRC_MODEL_EDGE_H_

#include "vertex.h"
namespace s21 {
class Edge {
 private:
  Vertex* m_p_begin_;
  Vertex* m_p_end_;

 public:
  Edge() : m_p_begin_(nullptr), m_p_end_(nullptr) {}
  Edge(Vertex& begin, Vertex& end);
  Edge(const Edge& other)
      : m_p_begin_(other.m_p_begin_), m_p_end_(other.m_p_end_) {}

  Vertex& GetBegin() { return *m_p_begin_; }
  Vertex& GetEnd() { return *m_p_end_; }
};
}  // namespace s21
#endif
