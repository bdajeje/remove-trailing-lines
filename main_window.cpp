#include "main_window.hpp"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

#include <boost/algorithm/string.hpp>

#include "utils.hpp"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  QWidget* main_widget = new QWidget(this);

  QVBoxLayout* main_layout = new QVBoxLayout(main_widget);

  _start_with = new QLineEdit;
  _start_with->setPlaceholderText("Files start with");

  _end_with = new QLineEdit;
  _end_with->setPlaceholderText("Files end with");

  QHBoxLayout* folder_layout = new QHBoxLayout;
  _selected_folder = new QLineEdit;
  QPushButton* _select_folder = new QPushButton("Select folder");
  folder_layout->addWidget(_select_folder);
  folder_layout->addWidget(_selected_folder);

  _recursive = new QCheckBox("Recursive");
  _recursive->setChecked(true);

  _start_button = new QPushButton("RUN");
  _start_button->setEnabled(false);

  _progress_bar = new QProgressBar;
  _progress_bar->setMinimum(0);

  main_layout->addLayout(folder_layout);
  main_layout->addWidget(_start_with);
  main_layout->addWidget(_end_with);
  main_layout->addWidget(_recursive);
  main_layout->addWidget(_start_button);
  main_layout->addWidget(_progress_bar);

  setCentralWidget(main_widget);

  connect( _select_folder, SIGNAL(pressed()), this, SLOT(selectFolder()) );
  connect( _start_button, SIGNAL(pressed()), this, SLOT(run()) );
  connect( _selected_folder, SIGNAL(textChanged(const QString&)), this, SLOT(updateRunButton(const QString&)) );
}

void MainWindow::updateRunButton(const QString& selected_folder)
{
  _start_button->setEnabled( selected_folder.isEmpty() ? false : true );
}

void MainWindow::selectFolder()
{
  _selected_folder->setText( QFileDialog::getExistingDirectory(this, tr("Select folder"), "/home",
                             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) );
}

void MainWindow::run()
{
  // Find files
  QStringList file_paths;
  const QString name_filter {_start_with->text() + "*" + _end_with->text()};
  utils::listFiles( _selected_folder->text(), name_filter, _recursive->isChecked(), file_paths );
  if(file_paths.empty())
  {
    QMessageBox::warning(this, "Empty result", "No files found");
    return;
  }

  // Reset progress bar
  _progress_bar->setValue(0);
  _progress_bar->setMaximum(file_paths.size());

  // Update files and save possible errors
  QStringList errors;
  for( const QString& file_path : file_paths )
  {
    if(!utils::removeTrailingLines(file_path.toStdString()))
      errors.append(file_path);

    _progress_bar->setValue( _progress_bar->value() + 1 );
  }

  // Some errors?
  if( !errors.empty() )
  {
    delete _files_error;
    _files_error = new EditFilesError(this, errors);
    _files_error->show();
  }

  // Output results to user
  const size_t nbr_files_updated = file_paths.size() - errors.size();
  if( nbr_files_updated > 0 )
    QMessageBox::information(this, "Information", (std::to_string(nbr_files_updated) + " file(s) have been found and updated").c_str());
}
