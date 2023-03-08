#pragma once
#include <QWidget>

namespace Ui {
class ListWidget;
}

struct Note;
class QListWidgetItem;

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget();

    void addNote(const Note& note);
    void removeCurrentNote();
    void updateCurrentNote(const Note& note);

    int currentNoteId();

signals:
    void selectedNoteChanged(int id);

private:
    void onItemSelectionChanged();

    void moveCurrentItemToTop(const Note& note);
    void setupNoteItem(const Note& note, QListWidgetItem* item);
private:
    Ui::ListWidget *ui;
};
