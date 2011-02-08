#ifndef POWERTABEDITOR_H
#define POWERTABEDITOR_H

#include <QMainWindow>

#include <memory>

#include <documentmanager.h>
#include <actions/undomanager.h>

class QTabWidget;
class ScoreArea;
class Mixer;
class QStackedWidget;
class SkinManager;
class PreferencesDialog;
class Toolbox;
class QSplitter;
class MidiPlayer;
class QSignalMapper;
class QActionGroup;
class QKeyEvent;
class QEvent;

class PowerTabEditor : public QMainWindow
{
    Q_OBJECT

    friend class NotePage;

public:
    PowerTabEditor(QWidget *parent = 0);
    ~PowerTabEditor();
    static void RefreshCurrentDocument();
    static QTabWidget* tabWidget;
    static std::unique_ptr<UndoManager> undoManager;
    static QSplitter* vertSplitter;
    static QSplitter* horSplitter;
    static ScoreArea* getCurrentScoreArea();

protected:
    void CreateActions();
    void CreateMenus();
    void CreateTabArea();
    void updateScoreAreaActions(bool disable);
    bool eventFilter(QObject *obj, QEvent *ev);

private slots:
    void updateActions();
    void OpenFile();
    void OpenPreferences();
    void RefreshOnUndoRedo(int);
    void closeCurrentTab();
    void closeTab(int index);
    void switchTab(int index);
    void startStopPlayback();
    bool moveCaretRight();
    bool moveCaretLeft();
    void moveCaretDown();
    void moveCaretUp();
    void moveCaretToStart();
    void moveCaretToEnd();
    bool moveCaretToPosition(quint8 position);

    bool moveCaretToNextStaff();
    bool moveCaretToPrevStaff();

    void moveCaretToFirstSection();
    bool moveCaretToNextSection();
    bool moveCaretToPrevSection();
    void moveCaretToLastSection();
    
    void moveCaretToNextBar();
    void moveCaretToPrevBar();

    void editChordName();
    void editRehearsalSign();
    void editNaturalHarmonic();
    void editNoteMuted();
    void editGhostNote();
    void editTiedNote();
    void editStaccato();
    void editHammerPull();

    void cycleTab(int offset);

    void updateNoteDuration(int duration);
    void shiftTabNumber(int direction);

private:
    bool isPlaying;

    Toolbox* toolBox;

    DocumentManager documentManager;
    QMenu* fileMenu;
    QAction* openFileAct;
    QAction* closeTabAct;
    QAction* preferencesAct;
    QAction* exitAppAct;

    QMenu* editMenu;
    QAction* undoAct;
    QAction* redoAct;

    QMenu* playbackMenu;
    QAction* playPauseAct;

    QMenu* positionMenu;
    QMenu* positionSectionMenu; // menu options for navigating between sections
    // navigate to the first, next, previous, or last section in the score
    QAction* firstSectionAct;
    QAction* nextSectionAct;
    QAction* prevSectionAct;
    QAction* lastSectionAct;

    QMenu* positionStaffMenu;
    QAction* nextPositionAct; // navigate to the next position in the staff
    QAction* prevPositionAct; // navigate to the previous position in the staff
    QAction* startPositionAct; // navigate to the first position in the staff
    QAction* lastPositionAct; // navigate to the last position in the staff
    QAction* nextStringAct; // navigate to the next string in the staff
    QAction* prevStringAct; // navigate to the previous string in the staff
    QAction* nextStaffAct; // navigate to the next staff in the system
    QAction* prevStaffAct; // navigate to the previous staff in the system
    QAction* nextBarAct; // navigate to the first non-bar pos in the next bar
    QAction* prevBarAct; // navigate to the first non-bar pos in the prev bar

    QAction* shiftTabNumUp; // shift tab numbers up/down by a string
    QAction* shiftTabNumDown;
    QSignalMapper* shiftTabNumberMapper;

    QMenu* textMenu;
    QAction* chordNameAct; // add/remove a chord name

    QMenu* notesMenu;
    QSignalMapper* noteDurationMapper; // map note duration signals to a slot
    QActionGroup* noteDurationActGroup; // only one duration can be checked at a time
    QAction* wholeNoteAct; // actions for modifying the duration of a note/rest
    QAction* halfNoteAct;
    QAction* quarterNoteAct;
    QAction* eighthNoteAct;
    QAction* sixteenthNoteAct;
    QAction* thirtySecondNoteAct;
    QAction* sixtyFourthNoteAct;
    QAction* tiedNoteAct; // sets a note to be tied to the previous note
    QAction* noteMutedAct; // sets the note to be muted
    QAction* ghostNoteAct; // set a note to be a ghost note
    QAction* staccatoNoteAct; // set the notes of a position to be staccato

    QMenu* musicSymbolsMenu;
    QAction* rehearsalSignAct; // add/remove rehearsal signs

    QMenu* tabSymbolsMenu;
    QAction* hammerPullAct; // add/remove hammer-on or pull-off
    QAction* naturalHarmonicAct; // add/remove natural harmonics

    QMenu* windowMenu;
    QAction* nextTabAct; // cycle to the next/previous tab
    QAction* prevTabAct;
    QSignalMapper* tabCycleMapper;

    QString previousDirectory; // previous directory that a file was opened in
    std::unique_ptr<QStackedWidget> mixerList;

    std::shared_ptr<SkinManager> skinManager;
    std::unique_ptr<MidiPlayer> midiPlayer;
};

#endif // POWERTABEDITOR_H
