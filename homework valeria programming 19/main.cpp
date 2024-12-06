//
//  main.cpp
//  homework valeria programming 19
//
//  Created by Valeria  Bukova on 07.12.2024.
//



#include <iostream>
using namespace std;


class Base
{
public:
    static int people_on_base;
    static int vehicles_on_base;
    static double petrol_on_base;
    static double goods_on_base;


    static void initBase(int people, int vehicles, double petrol, double goods) {
        people_on_base = people;
        vehicles_on_base = vehicles;
        petrol_on_base = petrol;
        goods_on_base = goods;
    }
};


int Base::people_on_base = 0;
int Base::vehicles_on_base = 0;
double Base::petrol_on_base = 0.0;
double Base::goods_on_base = 0.0;


class Vehicle {
protected:
    double petrol_amount;
    double tank_volume;

public:
    Vehicle(double petrol, double tank) : petrol_amount(petrol), tank_volume(tank) {}

    virtual void arrive() {
        Base::vehicles_on_base++;
        Base::people_on_base++;
    }

    virtual bool leave() {
        if (Base::petrol_on_base >= (tank_volume - petrol_amount) && Base::people_on_base > 0) {
            Base::petrol_on_base -= (tank_volume - petrol_amount);
            petrol_amount = tank_volume;
            Base::vehicles_on_base--;
            Base::people_on_base--;
            return true;
        }
        return false;
    }

    double getTankVolume() const { return tank_volume; }
    double getPetrolAmount() const { return petrol_amount; }
};


class Bus : public Vehicle {
private:
    int people_count;
    int max_people;
public:
    Bus(int people, int maxPeople, double petrol, double tank)
        : Vehicle(petrol, tank), people_count(people), max_people(maxPeople) {}

    void arrive() override {
        Base::vehicles_on_base++;
        Base::people_on_base += (people_count + 1);
        people_count = 0;
    }

    bool leave() override {
        int people_to_take = (max_people < Base::people_on_base - 1) ? max_people : Base::people_on_base - 1;
        if (Base::petrol_on_base >= (tank_volume - petrol_amount) && people_to_take > 0) {
            Base::petrol_on_base -= (tank_volume - petrol_amount);
            petrol_amount = tank_volume;
            Base::vehicles_on_base--;
            Base::people_on_base -= people_to_take;
            people_count = people_to_take;
            return true;
        }
        return false;
    }

    int getPeopleCount() const { return people_count; }
    int getMaxPeople() const { return max_people; }
};


class Truck : public Vehicle {
private:
    double current_load;
    double max_load;

public:
    Truck(double load, double maxLoad, double petrol, double tank)
        : Vehicle(petrol, tank), current_load(load), max_load(maxLoad) {}

    void arrive() override {
        Base::vehicles_on_base++;
        Base::people_on_base++;
        Base::goods_on_base += current_load;
        current_load = 0;
    }

    bool leave() override {
        double goods_to_take = (max_load < Base::goods_on_base) ? max_load : Base::goods_on_base;
        if (Base::petrol_on_base >= (tank_volume - petrol_amount) && goods_to_take > 0) {
            Base::petrol_on_base -= (tank_volume - petrol_amount);
            petrol_amount = tank_volume;
            Base::vehicles_on_base--;
            Base::people_on_base--;
            Base::goods_on_base -= goods_to_take;
            current_load = goods_to_take;
            return true;
        }
        return false;
    }

    double getCurrentLoad() const { return current_load; }
    double getMaxLoad() const { return max_load; }
};


int main() {
    
    Base::initBase(10, 2, 500.0, 20.0);

    
    Vehicle car(10.0, 50.0);
    Bus bus(5, 20, 20.0, 100.0);
    Truck truck(5.0, 10.0, 15.0, 200.0);

   
    car.arrive();
    cout << "After the car arrives:" << endl;
    cout << "People on base: " << Base::people_on_base << endl;
    cout << "Vehicles based on: " << Base::vehicles_on_base << endl;

   
    if (bus.leave()) {
        cout << "The bus successfully left the base." << endl;
    } else {
        cout << "The bus was unable to leave the base." << endl;
    }

    
    truck.arrive();
    cout << "After the truck arrives:" << endl;
    cout << "Cargo at base: " << Base::goods_on_base << " tons" << endl;
    cout << "Vehicles based on: " << Base::vehicles_on_base << endl;

    return 0;
}

