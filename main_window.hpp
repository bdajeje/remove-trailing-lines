#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QCheckBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>

#include "edit_files_error.hpp"

class MainWindow final : public QMainWindow
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
    QCheckBox* _recursive;
    QProgressBar* _progress_bar;

    EditFilesError* _files_error {nullptr};
};

#endif // MAIN_WINDOW_HPP
