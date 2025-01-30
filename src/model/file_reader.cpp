#include "file_reader.h"

namespace s21 {

void FileReader::findMinMax(double x, double y, double z) {
  if (x > m_max_x_) m_max_x_ = x;
  if (x < m_min_x_) m_min_x_ = x;
  if (y > m_max_y_) m_max_y_ = y;
  if (y < m_min_y_) m_min_y_ = y;
  if (z > m_max_z_) m_max_z_ = z;
  if (z < m_min_z_) m_min_z_ = z;
}

void FileReader::normalizingAndCentringFigure(s21::Figure &figure,
                                              NormalizationParameters &param) {
  double center_x = (m_max_x_ + m_min_x_) / 2.0;
  double center_y = (m_max_y_ + m_min_y_) / 2.0;
  double center_z = (m_max_z_ + m_min_z_) / 2.0;
  double range_x = m_max_x_ - m_min_x_;
  double range_y = m_max_y_ - m_min_y_;
  double range_z = m_max_z_ - m_min_z_;
  long double diagonalLength =
      sqrtl(range_x * range_x + range_y * range_y + range_z * range_z);
  if (diagonalLength == 0.0) diagonalLength = 1.0;
  long double scaleFactor = (long double)param.GetMaxRange() / diagonalLength;
  for (size_t i = 0; i < figure.GetVerticesRef().size(); ++i) {
    figure.GetVerticesRef()[i].GetPositionRef().X =
        (figure.GetVerticesRef()[i].GetPositionRef().X - center_x) *
        scaleFactor;
    figure.GetVerticesRef()[i].GetPositionRef().Y =
        (figure.GetVerticesRef()[i].GetPositionRef().Y - center_y) *
        scaleFactor;
    figure.GetVerticesRef()[i].GetPositionRef().Z =
        (figure.GetVerticesRef()[i].GetPositionRef().Z - center_z) *
        scaleFactor;
  }
}

void FileReader::discretizationFigure(Figure &figure,
                                      NormalizationParameters &param) {
  // Приведение к ближайшей точке сетки (Снэппинг)
  for (size_t i = 0; i < figure.GetVerticesRef().size(); ++i) {
    double x = figure.GetVerticesRef()[i].GetPositionRef().X;
    double y = figure.GetVerticesRef()[i].GetPositionRef().Y;
    double z = figure.GetVerticesRef()[i].GetPositionRef().Z;
    if (param.DxStep != 0.0)
      figure.GetVerticesRef()[i].GetPositionRef().X =
          std::round((x - m_min_x_) / param.DxStep) * param.DxStep + m_min_x_;
    if (param.DyStep != 0.0)
      figure.GetVerticesRef()[i].GetPositionRef().Y =
          std::round((y - m_min_y_) / param.DyStep) * param.DyStep + m_min_y_;
    if (param.DzStep != 0.0)
      figure.GetVerticesRef()[i].GetPositionRef().Z =
          std::round((z - m_min_z_) / param.DzStep) * param.DzStep + m_min_z_;
  }
}

void FileReader::resetMinMax() {
  m_max_x_ = 0.0;
  m_max_y_ = 0.0;
  m_max_z_ = 0.0;
  m_min_x_ = 0.0;
  m_min_y_ = 0.0;
  m_min_z_ = 0.0;
}

Figure *FileReader::ReadFigure(std::string path,
                               NormalizationParameters param) {
  resetMinMax();
  std::ifstream in_file;
  in_file.open(path);
  if (!in_file.is_open()) {
    std::cout << "Error: Can`t open file: " << path << std::endl;
    return nullptr;
  }
  Figure *figure = new Figure;
  figure->AddFileName(path);
  figure->GetFileName();
  std::stringstream ss;
  std::string line = "";
  std::string prefix = "";
  bool is_okey = true;
  while (std::getline(in_file >> std::ws, line) && is_okey) {
    ss.clear();
    ss.str(line);
    ss >> prefix;
    if (prefix == "v")  // Vertex position
    {
      double x = 0.0;
      double y = 0.0;
      double z = 0.0;
      if (ss >> x && ss >> y && ss >> z) {
        findMinMax(x, y, z);
        figure->AddNewVertex(x, y, z);
      } else {
        std::cout << "Error: Invalid vertex format in line: " << line
                  << std::endl;
        is_okey = false;
      }
    }
    if (prefix == "f")  // Vertex indicies
    {
      std::vector<int> vertex_indices;
      int tmp = 0;
      while ((ss >> tmp)) {
        if (tmp > 0) {
          if ((size_t)(tmp - 1) > figure->GetVerticesRef().size()) {
            std::cout << "Error: Invalid vertex indices > vertex count : "
                      << line << std::endl;
            is_okey = false;
          }
          vertex_indices.push_back(tmp - 1);
          tmp = 0;
        } else {
          std::cout << "Error: Invalid vertex indices format in line: " << line
                    << std::endl;
          is_okey = false;
        }
        ss.ignore(100, ' ');
      }
      if (vertex_indices.size() < 2) {
        std::cout << "Error: Invalid vertex indices count  in line: " << line
                  << std::endl;
        is_okey = false;
      }
      if (is_okey) {
        size_t i = 0;
        for (; i < vertex_indices.size() - 1; i++) {
          figure->AddNewEdge(vertex_indices[i], vertex_indices[i + 1]);
        }
        if (vertex_indices.size() > 2)
          figure->AddNewEdge(vertex_indices[i], vertex_indices[0]);
      }
    }
  }

  if (is_okey) {
    if (param.NeedDiscritization()) discretizationFigure(*figure, param);
    normalizingAndCentringFigure(*figure, param);
  } else {
    delete figure;
    figure = nullptr;
  }

  return figure;
}
}  // namespace s21
