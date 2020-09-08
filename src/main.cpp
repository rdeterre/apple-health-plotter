

#include "applehealthplotter.h"

#include "fmt/format.h"


using namespace date::literals;




int doit(int argc, char *argv[]) {
  QApplication a(argc, argv);

  //   health_data_t health_data{{{2015_y / date::March / 22, 1.1},
  //                              {2015_y / date::March / 23, 1.2},
  //                              {2015_y / date::March / 24, 1.1}}};
  // health_data_t health_data =
  //     parse_health_data("C:/users/romain/Desktop/export.xml");

  

  QAppleHealthPlotter window;
  window.resize(800, 600);
  window.show();
  return a.exec();
}

int main(int argc, char *argv[]) {
  try {
    std::cout << "Start\n";
    return doit(argc, argv);
  } catch (const std::exception &e) {
    std::cerr << "Failure: " << e.what() << "\n";
    return -1;
  }
}