#ifndef EDITFILESERROR_HPP
#define EDITFILESERROR_HPP

#include <QDialog>
#include <QStringListModel>

class EditFilesError final : public QDialog
{
  Q_OBJECT

  public:

    explicit EditFilesError(QWidget *parent, const QStringList& errors);
    ~EditFilesError();

  private:

    QStringListModel* _model;
};

#endif // EDITFILESERROR_HPP
