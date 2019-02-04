#include <vector>
#include <iostream>
#include <stdexcept>

#include "wagon.h"
#include "train.h"

using namespace std;

Train::Train(int own_mass, int max_mass, vector<Wagon> wagons) :
    own_mass(own_mass), max_mass(max_mass), wagons(wagons)
{
    if (own_mass > 200 || own_mass < 50 ||
        max_mass < 200 || max_mass > 10000)
        throw runtime_error("Invalid mass");
}

int Train::total_load() const
{
    unsigned int total{ own_mass };

    for (const auto &w : wagons)
        total += w.get_mass();

    return total;
}

bool Train::ready() const
{
    if (total_load() > max_mass)
        return false;

    int wagons_since_toilet{ 0 };
    vector<bool> features(5, false);

    for (const auto &w : wagons)
    {
        Feature feature{ w.get_feature() };
        bool has_toilet{ feature == Feature::Toilet };

        if (wagons_since_toilet == 3 && !has_toilet)
            return false;
        else if (has_toilet)
            wagons_since_toilet = 0;
        else
            ++wagons_since_toilet;

        features.at(static_cast<int>(feature)) = true;
    }

    for (const auto &b : features)
        if (!b)
            return false;

    return true;
}

void Train::couple(vector<Wagon> new_wagons)
{
    for (const auto &w : new_wagons)
        wagons.push_back(w);
}

vector<Wagon> Train::uncouple(size_t from)
{
    if (!(from < static_cast<size_t>(wagons.size())))
        throw runtime_error("");

    vector<Wagon> removed{}, new_wagons{};

    size_t i{ 0 };
    for (const auto &w : wagons)
    {
        if (i++ >= from)
            removed.push_back(w);
        else
            new_wagons.push_back(w);
    }

    wagons = new_wagons;

    return removed;
}

ostream& Train::print(ostream &o) const
{
    o << '[' << total_load() << '/' << max_mass << " tons, ";

    if (ready())
        o << "ready";
    else
        o << "not ready";

    o << " {";

    bool first = true;
    for (const auto &w : wagons)
    {
        if (!first)
            o << ", ";
        else
            first = false;

        o << w;
    }
    return o << "}]";
}

void Train::sort()
{
    vector<vector<Wagon>> categories(5, vector<Wagon>{});
    
    for (const auto &w : wagons)
        categories.at(static_cast<int>(w.get_feature())).push_back(w);

    vector<Wagon> new_wagons{};

    for (const auto &category : categories)
        for (const auto &w : category)
            new_wagons.push_back(w);

    wagons = new_wagons;
}

void Train::switches(size_t from, size_t count, Train &to, size_t pos)
{
    size_t this_size { wagons.size() };
    size_t other_size { to.wagons.size() };

    if (from >= this_size || from + count > this_size || pos > other_size || count <= 0)
        throw runtime_error("Invalid argument(s)");

    vector<Wagon> new_this_wagons{}, temp{}, new_other_wagons{};

    size_t i{ 0 };
    for (const auto &w : wagons)
    {
        if (i++ >= from && count--)
            temp.push_back(w);
        else
            new_this_wagons.push_back(w);
    }

    i = 0;
    bool inserted{ false };
    if (!to.wagons.empty())
    {
        for (const auto &w : to.wagons)
        {
            if (i++ == pos && !inserted)
            {
                for (const auto &temp_w : temp)
                    new_other_wagons.push_back(temp_w);
                inserted = true;
            }
            
            new_other_wagons.push_back(w);
        }
        to.wagons = new_other_wagons;
    }
    else
        to.wagons = temp;

    wagons = new_this_wagons;
}

ostream& operator<<(ostream &o, const Train &t)
{
    return t.print(o);
}

// [1, 2, 3, 4, 5]
// from = 2
// count = 3
// 
