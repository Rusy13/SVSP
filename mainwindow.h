#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class NotesManager;
struct Note;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(NotesManager& manager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void onNewNoteBtnClicked();
    void onRemoveBtnClicked();


    void onNewNoteCreated(int id);
    void onNoteContentChanged(int id);


    void onSelectedNoteChanged(int id);
    void onRemoveNote(int id);

private:
    void addNoteToList(const Note& note);
    void removeNote(int id);

    void init();
    void makeConnections();

    Ui::MainWindow *ui;
    NotesManager& notesManager;
};
#endif // MAINWINDOW_H
