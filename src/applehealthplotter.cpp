#include "applehealthplotter.h"

#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE;

void fill_series(
    QLineSeries *ser,
    const std::vector<std::pair<date::year_month_day, float>> &weigths) {
  for (auto weigth : weigths) {
    ser->append(
        date::sys_time<std::chrono::milliseconds>(date::sys_days(weigth.first))
            .time_since_epoch()
            .count(),
        weigth.second);
  }
}

health_data_t parse_health_data(std::string filename) {
  health_data_t out;
  pugi::xml_document doc;
  const auto result = doc.load_file(filename.c_str());
  if (!result)
    throw std::runtime_error(
        fmt::format("XML parsed with errors: {}. Error offset: {}",
                    std::string(result.description()), result.offset));

  const auto healthdata = doc.child("HealthData");
  if (!healthdata)
    throw std::runtime_error(fmt::format("HealthData missing from file"));

  for (pugi::xml_node record = healthdata.child("Record"); record;
       record = record.next_sibling("Record")) {
    if (std::string(record.attribute("type").value()) ==
        "HKQuantityTypeIdentifierBodyMass") {
      std::istringstream in{record.attribute("startDate").value()};
      date::sys_time<std::chrono::milliseconds> tp;
      in >> date::parse("%F %T %z", tp);
      date::year_month_day ymd{floor<date::days>(tp)};
      out.weigths.push_back(
          {ymd, std::atof(record.attribute("value").value())});
    }
  }

  std::sort(out.weigths.begin(), out.weigths.end(),
            [](const auto &left, const auto &right) {
              return left.first < right.first;
            });

  return out;
}

void QAppleHealthPlotter::update_ui() {
  QLineSeries *series = new QLineSeries();

  fill_series(series, health_data_.weigths);

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series);

  QDateTimeAxis *axisX = new QDateTimeAxis;
  axisX->setTickCount(10);
  axisX->setFormat("yyyy MMM dd");
  axisX->setTitleText("Date");
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);
  QValueAxis *axisY = new QValueAxis;
  axisY->setTitleText("Poids");
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chart->setTitle("Poids (kg)");

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  setCentralWidget(chartView);
}

QAppleHealthPlotter::QAppleHealthPlotter(QWidget *parent)
    : QMainWindow(parent) {
  auto openFile = new QAction("Ouvrir");
  connect(openFile, &QAction::triggered, [this] {
    QString filename =
        QFileDialog::getOpenFileName(this, "Fichier XML à ouvrir", "", "*.xml");
    if (filename.isEmpty())
      return;
    try {
      health_data_ = parse_health_data(filename.toStdString());
      update_ui();
    } catch (const std::exception &e) {
      QMessageBox::critical(
          this, "Echec the l'ouverture",
          fmt::format("L'ouverture du fichier {} a échoué: {}",
                      filename.toStdString(), e.what())
              .c_str());
    }
  });

  auto fileMenu = menuBar()->addMenu(tr("&Fichier"));
  fileMenu->addAction(openFile);
}
