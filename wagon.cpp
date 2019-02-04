#include <iostream>
#include <stdexcept>

#include "wagon.h"

using namespace std;

Wagon::Wagon(int mass, Feature feature) :
    mass(mass), feature(feature)
{
    if (mass < 5 || mass > 100)
        throw runtime_error("Invalid mass");
}

int Wagon::get_mass() const
{
    return mass;
}

Feature Wagon::get_feature() const
{
    return feature;
}

bool Wagon::has_feature(Feature f) const
{
    return feature == f;
}

ostream& Wagon::print(ostream &o) const
{
    return o << "[mass: " << mass << " tons "
             << feature_names.at(static_cast<int>(feature))
             << "-wagon]";
}

ostream& operator<<(ostream &o, const Wagon &w)
{
    return w.print(o);
}
