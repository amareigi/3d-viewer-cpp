#include "status_widget.h"

#include <QDebug>

namespace s21 {
StatusWidget::StatusWidget(QWidget* parent) : QWidget{parent} {
  m_p_active_figure_path_ = new QLineEdit(this);
  m_p_active_figure_path_->setText("The figure is not loaded");
  m_p_active_figure_path_->setReadOnly(true);

  m_p_vertex_num_ = new QLCDNumber(12);
  m_p_edge_num_ = new QLCDNumber(12);
  m_p_loaded_figures_num_ = new QLCDNumber(12);
  m_p_active_figure_num_ = new QLCDNumber(12);

  m_p_vertex_num_->setSegmentStyle(QLCDNumber::Flat);
  m_p_edge_num_->setSegmentStyle(QLCDNumber::Flat);
  m_p_loaded_figures_num_->setSegmentStyle(QLCDNumber::Flat);
  m_p_active_figure_num_->setSegmentStyle(QLCDNumber::Flat);

  m_p_vertex_num_->display(0);
  m_p_edge_num_->display(0);
  m_p_loaded_figures_num_->display(0);
  m_p_active_figure_num_->display(0);

  QLabel* vertex_lbl = new QLabel("Vertices count");
  QLabel* edge_lbl = new QLabel("Edges count");
  QLabel* loaded_figures_lbl = new QLabel("Loaded figures");
  QLabel* active_figure_lbl = new QLabel("Active figure");

  QGridLayout* lcdLayout = new QGridLayout();
  lcdLayout->addWidget(vertex_lbl, 0, 0);
  lcdLayout->addWidget(edge_lbl, 1, 0);
  lcdLayout->addWidget(loaded_figures_lbl, 2, 0);
  lcdLayout->addWidget(active_figure_lbl, 3, 0);
  lcdLayout->addWidget(m_p_vertex_num_, 0, 1);
  lcdLayout->addWidget(m_p_edge_num_, 1, 1);
  lcdLayout->addWidget(m_p_loaded_figures_num_, 2, 1);
  lcdLayout->addWidget(m_p_active_figure_num_, 3, 1);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(m_p_active_figure_path_);
  layout->addLayout(lcdLayout);

  setLayout(layout);
}

void StatusWidget::onStatusUpdated(int v, int e, int f, int a, QString path) {
  m_p_vertex_num_->display(v);
  m_p_edge_num_->display(e);
  m_p_loaded_figures_num_->display(f);
  m_p_active_figure_num_->display(a);
  m_p_active_figure_path_->setText(path);
}
}  // namespace s21
