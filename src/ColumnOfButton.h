#ifndef CLUMNOFBUTTON_H
#define CLUMNOFBUTTON_H

#include <vector>
#include <QPushButton>

using namespace std;

class ColumnOfButton {
public:
    void push(QPushButton *btn) {
        buttons.insert(buttons.end(), btn);
    }
    QPushButton *getByIndex(unsigned int index);
    QPushButton *getLast() {
        return getByIndex(buttons.size() - 1);
    }

    unsigned int size() {
        return buttons.size();
    }

    QPushButton *popLast() {
        QPushButton *button = getByIndex(buttons.size()-1);
        buttons.pop_back();
        return button;
    }

private:
    vector <QPushButton*> buttons;
};

#endif // CLUMNOFBUTTON_H
