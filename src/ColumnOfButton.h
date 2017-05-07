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
    unsigned int size() {
        return buttons.size();
    }

private:
    vector <QPushButton*> buttons;
};

#endif // CLUMNOFBUTTON_H
