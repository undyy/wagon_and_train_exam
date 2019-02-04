#ifndef WAGON_H
#define WAGON_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Feature
{
    Bar, Restaurant, Couchette, Standard, Toilet
};

const vector<string> feature_names {"bar", "restaurant", 
    "couchette", "standard", "toilet"};

class Wagon
{
    private:
        int mass;
        Feature feature;

    public:
        Wagon(int mass, Feature feature=Feature::Standard);

        int get_mass() const;
        Feature get_feature() const;
        bool has_feature(Feature f) const;
        ostream& print(ostream &o) const;
};

ostream& operator<<(ostream &o, const Wagon &w);

#endif
