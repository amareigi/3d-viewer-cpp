#include "figure.h"

namespace s21 {

std::deque<Vertex> &Figure::GetVerticesRef() { return m_vertices_; }

std::vector<Edge> &Figure::GetEdgesRef() { return m_edges_; }

void Figure::AddFileName(std::string name) { m_file_name_ = name; }

std::string Figure::GetFileName() { return m_file_name_; }

void Figure::AddNewVertex(double x, double y, double z) {
  m_vertices_.push_back(Vertex(x, y, z));
}

void s21::Figure::AddNewEdge(int begin, int end) {
  m_edges_.push_back(Edge(m_vertices_[begin], m_vertices_[end]));
}

}  // namespace s21
