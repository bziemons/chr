#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <testtui_lib.h>

#include "file.h"
#include "clipboard.h"

class SearchDialog : public Dialog {
    Q_OBJECT

public:
    SearchDialog(Tui::ZWidget *parent, bool replace = false);
    void setSearchText(QString text);
    void setReplace(bool replace);

signals:
    void caseSensitiveChanged(bool value);
    void wrapChanged(bool value);
    void forwardChanged(bool value);
    void canceled();
    void liveSearch(QString text, bool forward);
    void findNext(QString text, bool regex, bool forward);
    void replace1(QString text, QString replacement, bool regex, bool forward);
    void replaceAll(QString text, QString replacement, bool regex);

public slots:
    void open();

private:
    bool _replace = false;
    InputBox *_searchText = nullptr;
    InputBox *_replaceText = nullptr;
    Button *_findNextBtn = nullptr;
    Button *_findPreviousBtn = nullptr;
    Button *_cancelBtn = nullptr;
    Button *_replaceBtn = nullptr;
    Button *_replaceAllBtn = nullptr;
    bool _caseSensitive = true;
    CheckBox *_caseMatchBox = nullptr;
    CheckBox *_parseBox = nullptr;
    CheckBox *_wrapBox = nullptr;
    CheckBox *_regexMatchBox = nullptr;
    CheckBox *_liveSearchBox = nullptr;
    RadioButton *_forward = nullptr;
    RadioButton *_backward = nullptr;
};

#endif // SEARCHDIALOG_H
