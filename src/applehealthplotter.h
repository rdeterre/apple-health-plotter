#pragma once

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

#include <QtCore/QDate>
#include <QtCore/QDateTime>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>

#include "date/date.h"
#include "fmt/format.h"
#include "pugixml.hpp"

struct health_data_t {
  std::vector<std::pair<date::year_month_day, float>> weigths;
};

health_data_t parse_health_data(std::string filename);

class QAppleHealthPlotter : public QMainWindow {
  Q_OBJECT
  health_data_t health_data_;

public:
  QAppleHealthPlotter(QWidget *parent = nullptr);

  void update_ui();
};