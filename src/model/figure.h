#ifndef S21_SRC_MODEL_FIGURE_H_
#define S21_SRC_MODEL_FIGURE_H_

#include <deque>
#include <string>
#include <vector>

#include "edge.h"
#include "vertex.h"

namespace s21 {
class Figure {
 private:
  std::string m_file_name_;
  std::deque<Vertex> m_vertices_;
  std::vector<Edge> m_edges_;

 public:
  // по правилу пяти запрятить всё лишнее
  Figure(){};

  std::deque<Vertex>& GetVerticesRef();
  std::vector<Edge>& GetEdgesRef();

  void AddFileName(std::string name);
  std::string GetFileName();

  void AddNewVertex(double x, double y, double z);
  void AddNewEdge(int begin, int end);
};
}  // namespace s21
#endif
