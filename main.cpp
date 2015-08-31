#include "main_window.hpp"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("Remove Trailing Lines");

  MainWindow window;
  QIcon icon(QDir(argv[0]).dirName() + QString("/resources/icon.png"));
  window.setWindowIcon(icon);
  window.show();

  return app.exec();
}
