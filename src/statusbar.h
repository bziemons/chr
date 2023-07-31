// SPDX-License-Identifier: BSL-1.0

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <Tui/ZColor.h>
#include <Tui/ZWidget.h>


class StatusBar : public Tui::ZWidget {
    Q_OBJECT
public:
    StatusBar(Tui::ZWidget *parent);
    QString viewCursorPosition();
    QString viewFileChanged();
    QString viewMsdosMode();
    QString viewModifiedFile();
    QString viewOverwrite();
    QString viewReadWriete();
    QString viewSelectMode();
    QString viewStandardInput();

public:
    QSize sizeHint() const override;

public slots:
    void cursorPosition(int x, int utf8x, int y);
    void scrollPosition(int x, int y);
    void setModified(bool modifiedFile);
    void readFromStandardInput(bool activ);
    void followStandardInput(bool follow);
    void setWritable(bool rw);
    void searchCount(int sc);
    void searchText(QString searchText);
    void msdosMode(bool msdos);
    void modifiedSelectMode(bool f4);
    void fileHasBeenChangedExternally(bool fileChanged = true);
    void overwrite(bool overwrite);

protected:
    void paintEvent(Tui::ZPaintEvent *event);

private:
    bool _modifiedFile = false;
    int _cursorPositionX = 0;
    int _utf8PositionX = 0;
    int _cursorPositionY = 0;
    int _scrollPositionX = 0;
    int _scrollPositionY = 0;
    bool _stdin = false;
    bool _follow = false;
    bool _readwrite = true;
    int _searchCount = -1;
    QString _searchText = "";
    bool _msdosMode = false;
    bool _selectMode = false;
    bool _fileChanged = false;
    bool _overwrite = false;
    Tui::ZColor _bg;
};

#endif // STATUSBAR_H
