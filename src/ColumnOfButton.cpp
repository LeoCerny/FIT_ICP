#include "ColumnOfButton.h"
#include <stdexcept>

QPushButton *ColumnOfButton::getByIndex(unsigned int index)  {
    if (index >= this->buttons.size())
        throw invalid_argument("Mimo rozsah");
    return buttons.at(index);
}
