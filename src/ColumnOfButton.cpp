#include "ColumnOfButton.h"

QPushButton *ColumnOfButton::getByIndex(unsigned int index)  {
    if (index >= size())
        throw invalid_argument("Mimo rozsah");
    return buttons.at(index);
}
