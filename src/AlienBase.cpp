//header

#include "AlienBase.h"
#include <string>
using namespace std;

AlienBase::AlienBase() {
    name = "TEMP NAME";
}

string AlienBase::getName() const {
    return name;
}