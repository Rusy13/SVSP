#pragma once
#include <QObject>
#include <unordered_map>
#include <vector>
#include <utility>
#include <memory>
#include <note.h>

struct Note;

class QTextDocument;
class QSignalMapper;

class NotesManager : public QObject
{
    Q_OBJECT
public:
    explicit NotesManager(QObject *parent = nullptr);
    ~NotesManager();

    void createNewNote();
    void removeNote(int id);
    void renameNote(int id, const QString& newTitle);

    const Note& note(int id) const;
    QTextDocument* noteDocument(int id) const;
    std::vector<std::reference_wrapper<Note>> noteCollection();
    size_t count() const;

signals:
    void newNoteCreated(int id);
    void noteContentChanged(int id);

private:
    void onNoteContentChanged(int id);

    void readNotes();
    void writeNotes();
    std::unique_ptr<QTextDocument> createNewTextDocument(const Note& note);

private:
    std::unordered_map<int, std::pair<Note, std::unique_ptr<QTextDocument>>> notes;

    QSignalMapper* mapChangedSignalToNoteId = nullptr;
};





