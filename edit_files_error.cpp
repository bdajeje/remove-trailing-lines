#include "edit_files_error.hpp"

#include <QLabel>
#include <QListView>
#include <QVBoxLayout>

EditFilesError::EditFilesError(QWidget *parent, const QStringList& errors)
  : QDialog {parent}
  , _model { new QStringListModel(errors) }
{
  setWindowTitle("Edit files error");

  QVBoxLayout* main_layout = new QVBoxLayout(this);

  QLabel* intro = new QLabel("The following file(s) couldn't be edited");
  QListView* errors_list = new QListView;
  errors_list->setModel(_model);

  main_layout->addWidget(intro);
  main_layout->addWidget(errors_list);
}

EditFilesError::~EditFilesError()
{
  delete _model;
}
