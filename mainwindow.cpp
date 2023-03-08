#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notesmanager.h"
#include "note.h"
#include "listwidget.h"

#include <QPushButton>
#include <QMessageBox>


MainWindow::MainWindow(NotesManager& manager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , notesManager(manager)
{

    ui->setupUi(this);

    makeConnections();
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onNewNoteBtnClicked()
{
    notesManager.createNewNote();
}

void MainWindow::onRemoveBtnClicked()
{
    removeNote(ui->notesListWidget->currentNoteId());
}

void MainWindow::onNewNoteCreated(int id)
{
    addNoteToList(notesManager.note(id));
}

void MainWindow::onNoteContentChanged(int id)
{
    ui->notesListWidget->updateCurrentNote(notesManager.note(id));
}

void MainWindow::onSelectedNoteChanged(int id)
{
    auto* document = notesManager.noteDocument(id);
    if(document)
    {
        ui->textEdit->setDocument(document);
        auto cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::onRemoveNote(int id)
{
    removeNote(id);
}


void MainWindow::addNoteToList(const Note &note)
{
    ui->notesListWidget->addNote(note);
}

void MainWindow::removeNote(int id)
{
    QString noteTitle = notesManager.note(id).title;


    auto pressedBtn = QMessageBox::information(this, "Удалить?",
                                               QString("Подтвердить?").arg(noteTitle),
                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if(pressedBtn == QMessageBox::Yes)
    {
        if(notesManager.count()==1)
            ui->textEdit->setDocument(nullptr);

        ui->notesListWidget->removeCurrentNote();
        notesManager.removeNote(id);
    }
}

void MainWindow::init()
{

    auto notesList = notesManager.noteCollection();
    std::sort(notesList.begin(), notesList.end(),
              [](const Note& left, const Note& right)
              {
                  return left.lastModified < right.lastModified;
              });

    for(auto& note : notesList)
    {
        addNoteToList(note);
    }
}

void MainWindow::makeConnections()
{
    connect(ui->NewBtn, &QPushButton::clicked, this, &MainWindow::onNewNoteBtnClicked);
    connect(ui->RemBtn, &QPushButton::clicked, this, &MainWindow::onRemoveBtnClicked);

    connect(&notesManager, &NotesManager::newNoteCreated, this, &MainWindow::onNewNoteCreated);
    connect(&notesManager, &NotesManager::noteContentChanged, this, &MainWindow::onNoteContentChanged);

    connect(ui->notesListWidget, &ListWidget::selectedNoteChanged,this, &MainWindow::onSelectedNoteChanged);
}

