#include "../third-party/catch.hpp"
//#include "tests/Testhelper.h"
#include "Tui/ZTerminal.h"
#include "Tui/ZTest.h"
#include "Tui/ZRoot.h"
#include "file.h"
#include "documenttests.h"
#include "document.h"

class Rootabgeletiet : public Tui::ZRoot {
public:
    QObject *facet(const QMetaObject &metaObject) override {
        if (metaObject.className()  == Clipboard::staticMetaObject.className()) {
            return &_clipboard;
        } else {
            return ZRoot::facet(metaObject);
        }
    }

private:
    Clipboard _clipboard;
};


TEST_CASE("file") {
    Tui::ZTerminal::OffScreen of(80, 24);
    Tui::ZTerminal terminal(of);
    Rootabgeletiet root;
    Tui::ZWindow *w = new Tui::ZWindow(&root);
    terminal.setMainWidget(&root);
    w->setGeometry({0, 0, 80, 24});


    File *f = new File(w);
    f->setFocus();
    f->setGeometry({0, 0, 80, 24});

    //OHNE TEXT
    CHECK(f->getCursorPosition() == QPoint{0,0});

    //struct TestCase { Qt::KeyboardModifiers mod; };
    auto testCase = GENERATE(Qt::KeyboardModifier::NoModifier, Qt::KeyboardModifier::AltModifier, Qt::KeyboardModifier::MetaModifier,
                             Qt::KeyboardModifier::ShiftModifier, Qt::KeyboardModifier::KeypadModifier, Qt::KeyboardModifier::ControlModifier,
                             Qt::KeyboardModifier::GroupSwitchModifier, Qt::KeyboardModifier::KeyboardModifierMask);

    SECTION("key-left") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Left, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-right") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Right, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-up") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Up, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-down") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Down, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-home") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Home, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
        Tui::ZTest::sendKey(&terminal, Qt::Key_Home, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-end") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_End, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-page-up") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_PageUp, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-page-down") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_PageDown, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-enter") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Enter, testCase);
        if (Qt::KeyboardModifier::NoModifier == testCase || Qt::KeyboardModifier::KeypadModifier == testCase) {
            CHECK(f->getCursorPosition() == QPoint{0,1});
        } else {
            CHECK(f->getCursorPosition() == QPoint{0,0});
        }
    }
    SECTION("key-tab") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Tab, testCase);
        if (Qt::KeyboardModifier::NoModifier == testCase) {
            CHECK(f->getCursorPosition() == QPoint{8,0});
            //TODO: CHECK(f->getText == "        ");
        } else {
            CHECK(f->getCursorPosition() == QPoint{0,0});
        }
    }
    SECTION("key-insert") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Insert, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-delete") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Delete, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    SECTION("key-escape") {
        Tui::ZTest::sendKey(&terminal, Qt::Key_Escape, testCase);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
}

TEST_CASE("actions") {
    Tui::ZTerminal::OffScreen of(80, 24);
    Tui::ZTerminal terminal(of);
    Rootabgeletiet root;
    Tui::ZWindow *w = new Tui::ZWindow(&root);
    terminal.setMainWidget(&root);
    w->setGeometry({0, 0, 80, 24});

    File *f = new File(w);

    DocumentTestHelper t;

    Document &doc = t.getDoc(f);
    TextCursor cursor{&doc, f};

    f->setFocus();
    f->setGeometry({0, 0, 80, 24});

    CHECK(f->getCursorPosition() == QPoint{0,0});
    Tui::ZTest::sendText(&terminal, "    text", Qt::KeyboardModifier::NoModifier);

    SECTION("pos1pos1") {
        CHECK(f->getCursorPosition() == QPoint{8,0});
        Tui::ZTest::sendKey(&terminal, Qt::Key_Home, Qt::KeyboardModifier::NoModifier);
        CHECK(f->getCursorPosition() == QPoint{0,0});
        Tui::ZTest::sendKey(&terminal, Qt::Key_Home, Qt::KeyboardModifier::NoModifier);
        CHECK(f->getCursorPosition() == QPoint{4,0});
        Tui::ZTest::sendKey(&terminal, Qt::Key_Home, Qt::KeyboardModifier::NoModifier);
        CHECK(f->getCursorPosition() == QPoint{0,0});
    }
    //Tui::ZTest::sendKey(&terminal, Qt::Key_PageUp, Qt::KeyboardModifier::ControlModifier);

    //TODO:
    Tui::ZTest::sendKey(&terminal, Qt::Key_Enter, Qt::KeyboardModifier::NoModifier);
    Tui::ZTest::sendText(&terminal, "    new1", Qt::KeyboardModifier::NoModifier);
    //CHECK(doc._text.size() == 2);

    SECTION("acv") {
        Tui::ZTest::sendText(&terminal, "a", Qt::KeyboardModifier::ControlModifier);
        Tui::ZTest::sendText(&terminal, "c", Qt::KeyboardModifier::ControlModifier);
        CHECK(f->getCursorPosition() == QPoint{8,1});
        Tui::ZTest::sendText(&terminal, "v", Qt::KeyboardModifier::ControlModifier);
        //TODO FALSCH
        CHECK(f->getCursorPosition() == QPoint{0,2});
    }
    SECTION("axv") {
        Tui::ZTest::sendText(&terminal, "a", Qt::KeyboardModifier::ControlModifier);
        CHECK(f->getCursorPosition() == QPoint{8,1});
        CHECK(f->isSelect() == true);
        Tui::ZTest::sendText(&terminal, "x", Qt::KeyboardModifier::ControlModifier);
        CHECK(f->getCursorPosition() == QPoint{0,0});
        CHECK(f->isSelect() == false);
        Tui::ZTest::sendText(&terminal, "v", Qt::KeyboardModifier::ControlModifier);
        //TODO FALSCH
        CHECK(f->isSelect() == false);
        CHECK(f->getCursorPosition() == QPoint{0,2});
    }


    SECTION("sort") {
        // Alt + Shift + s sort selected lines
        //CAPTURE(doc._text[1]);
        CHECK(doc._text.size() == 2);
        CHECK(doc._text[1] == "    new1");
        Tui::ZTest::sendText(&terminal, "a", Qt::KeyboardModifier::ControlModifier);
        CHECK(f->isSelect() == true);
        Tui::ZTest::sendText(&terminal, "S", Qt::KeyboardModifier::AltModifier | Qt::KeyboardModifier::ShiftModifier);
        CHECK(doc._text[0] == "    new1");
        CHECK(doc._text.size() == 2);
        CHECK(f->isSelect() == true);
    }
    SECTION("key-left") {
        CHECK(f->getCursorPosition() == QPoint{8,1});
        Tui::ZTest::sendKey(&terminal, Qt::Key_Left, Qt::KeyboardModifier::NoModifier);
        CHECK(f->getCursorPosition() == QPoint{7,1});
    }

    SECTION("scroll") {
        auto testCase = GENERATE(ZTextOption::WrapMode::NoWrap, ZTextOption::WrapMode::WordWrap, ZTextOption::WrapMode::WrapAnywhere);
        f->setWrapOption(testCase);
        //TODO
        CHECK(f->getScrollPosition() == QPoint{0,0});
        //Tui::ZTest::sendText(&terminal, QString("a").repeated(100), Qt::KeyboardModifier::NoModifier);

        for (int i = 0; i < 48; i++) {
            Tui::ZTest::sendKey(&terminal, Qt::Key_Enter, Qt::KeyboardModifier::NoModifier);
        }
        CHECK(f->getScrollPosition() == QPoint{0,27});
        CHECK(f->getCursorPosition() == QPoint{0,49});
        for (int i = 0; i <= 26; i++) {
            Tui::ZTest::sendKey(&terminal, Qt::Key_Up, Qt::KeyboardModifier::ControlModifier);
            CHECK(f->getScrollPosition() == QPoint{0,26 - i});
            CHECK(f->getCursorPosition() == QPoint{0,48 - i});
        }
    }

    //TODO Scroll with Wrap and Wrapt lines.
}
