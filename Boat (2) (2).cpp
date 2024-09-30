#include "Boat.h"
#include <iostream>

Boat::Boat(int lgth, const std::vector<int>& r, const std::vector<int>& c, const std::string& nme, char dir)
    : length(lgth), boatrow(r), boatcol(c), name(nme), direction(dir) {}

void Boat::setHit() {
    hits++;
}

bool Boat::checkSunk() const {
    return hits >= length;
}

std::string Boat::getName() const {
    return name;
}

bool Boat::isHit(int row, int col) const {
    for (size_t i = 0; i < boatrow.size(); i++) {
        if (boatrow[i] == row && boatcol[i] == col) {
            return true;
        }
    }
    return false;
}
