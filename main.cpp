#include "main_window.hpp"

#include <QApplication>

std::string getFolder(const std::string& path)
{
  size_t offset = path.find_last_of("/");
  if(offset == std::string::npos)
    return path;

  return path.substr(0, offset);
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("Remove Trailing Lines");

  MainWindow window;
  QIcon icon((getFolder(argv[0]) + "/resources/icon.png").c_str());
  window.setWindowIcon(icon);
  window.show();

  return app.exec();
}
