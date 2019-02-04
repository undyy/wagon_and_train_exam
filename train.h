#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <iostream>

#include "wagon.h"

using namespace std;

class Train
{
    private:
        unsigned int own_mass, max_mass;
        vector<Wagon> wagons;

    public:
        Train(int own_mass, int max_mass, vector<Wagon> wagons={});

        int total_load() const;
        bool ready() const;
        void couple(vector<Wagon> new_wagons);
        vector<Wagon> uncouple(size_t from);
        ostream& print(ostream &o) const;
        
        void sort();
        void switches(size_t from, size_t count, Train &to, size_t pos);
};

ostream& operator<<(ostream &o, const Train &t);

#endif
