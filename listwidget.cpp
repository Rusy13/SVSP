#include "listwidget.h"
#include "ui_listwidget.h"

#include "note.h"

ListWidget::ListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget)
{
    ui->setupUi(this);

    connect(ui->noteList, &QListWidget::itemSelectionChanged,
            this, &ListWidget::onItemSelectionChanged);
}

ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::addNote(const Note &note)
{
    auto* item = new QListWidgetItem();
    ui->noteList->insertItem(0, item);

    setupNoteItem(note, item);
}

void ListWidget::removeCurrentNote()
{
    auto* currentItem = ui->noteList->currentItem();
    if(currentItem != nullptr)
    {
        delete currentItem;
    }
}

void ListWidget::updateCurrentNote(const Note &note)
{
    if(ui->noteList->currentRow() != 0)
    {
        moveCurrentItemToTop(note);
    }
}

int ListWidget::currentNoteId()
{
    auto* currentItem = ui->noteList->currentItem();
    int noteId = currentItem->data(Qt::UserRole).toInt();
    return noteId;
}

void ListWidget::onItemSelectionChanged()
{
    auto* currentItem = ui->noteList->currentItem();
    if(currentItem)
    {
        int id = currentNoteId();

        emit selectedNoteChanged(id);
    }
}

void ListWidget::moveCurrentItemToTop(const Note &note)
{
    blockSignals(true);
    auto* item = ui->noteList->takeItem(ui->noteList->currentRow());

    ui->noteList->insertItem(0, item);
    setupNoteItem(note,item);
    blockSignals(false);
}

void ListWidget::setupNoteItem(const Note &note, QListWidgetItem *item)
{
    item->setText(note.title);
    item->setData(Qt::UserRole, note.id);
    ui->noteList->setCurrentItem(item);
}
