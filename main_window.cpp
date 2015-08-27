#include "main_window.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

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

  _start_button = new QPushButton("RUN");
  _start_button->setEnabled(false);

  main_layout->addLayout(folder_layout);
  main_layout->addWidget(_start_with);
  main_layout->addWidget(_end_with);
  main_layout->addWidget(_start_button);

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
  const auto& file_paths = utils::listFiles( _selected_folder->text().toStdString(), _start_with->text().toStdString(), _end_with->text().toStdString() );
  if(file_paths.empty())
  {
    QMessageBox::warning(this, "Empty result", "No files found");
    return;
  }

  // Update files and save possible errors
  std::vector<std::string> errors;
  for( const auto& file_path : file_paths )
  {
    if(!utils::removeTrailingLines(file_path))
      errors.push_back(file_path);
  }

  // Some errors?
  if( !errors.empty() )
  {
    // Create error message
    QString error_msg {"The following file(s) couldn't be edited (may be you don't have the correct permissions):\n"};
    for(const auto& error : errors)
      error_msg += (error + "\n").c_str();

    // Show error message
    QMessageBox::warning(this, "Errors", error_msg);
  }

  // Output results to user
  const size_t nbr_files_updated = file_paths.size() - errors.size();
  if( nbr_files_updated > 0 )
    QMessageBox::information(this, "Information", (std::to_string(nbr_files_updated) + " file(s) have been updated").c_str());
}
