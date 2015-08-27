#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:

    MainWindow(QWidget *parent = 0);

  private slots:

    void selectFolder();
    void run();
    void updateRunButton(const QString& selected_folder);

  private:

    QLineEdit* _selected_folder;
    QLineEdit* _start_with;
    QLineEdit* _end_with;
    QPushButton* _start_button;
};

#endif // MAIN_WINDOW_HPP
