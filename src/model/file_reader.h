#ifndef S21_SRC_MODEL_FILE_READER_H_
#define S21_SRC_MODEL_FILE_READER_H_

#include <chrono>  // для замеров
#include <cmath>   //sqrt
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "base_file_reader.h"
namespace s21 {
class FileReader : public BaseFileReader {
 private:
  double m_max_x_;
  double m_max_y_;
  double m_max_z_;
  double m_min_x_;
  double m_min_y_;
  double m_min_z_;

  void findMinMax(double x, double y, double z);

  void normalizingAndCentringFigure(Figure& figure,
                                    NormalizationParameters& param);

  void discretizationFigure(Figure& figure, NormalizationParameters& param);

 public:
  FileReader(){};

  ~FileReader() = default;

  void resetMinMax();

  Figure* ReadFigure(std::string path, NormalizationParameters param) override;
};
}  // namespace s21
#endif
