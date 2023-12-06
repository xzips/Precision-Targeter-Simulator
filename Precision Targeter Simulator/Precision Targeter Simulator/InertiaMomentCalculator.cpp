/*
InertialMomentCalculator.cpp

This class is used to define the mass distribution of the rotating mechanism dynamically, as it may change as the prototype is iterated.
This class also allows automatic computing of the rotational moment of inertia, I, of the rotating mechanism given the mass distribution.

Three mass types are defined: disk mass and hollow cylinder mass.

For each struct, mass is the total mass of that chunk, and distance is the distance from the center of rotation to the center of mass of that chunk.
Other parameters are self-explanatory.
*/

#include "InertiaMomentCalculator.hpp"

InertiaMomentCalculator::Shape::Shape(double m, double r, double d) : mass(m), radius(r), distance(d) {}

InertiaMomentCalculator::Shape::~Shape() {}

InertiaMomentCalculator::Disk::Disk(double m, double r, double d) : Shape(m, r, d) {}

double InertiaMomentCalculator::Disk::ComputeMomentOfInertia() {
    double I_center = 0.5 * mass * radius * radius;
    return I_center + mass * distance * distance;
}

InertiaMomentCalculator::HollowCylinder::HollowCylinder(double m, double r, double d) : Shape(m, r, d) {}

double InertiaMomentCalculator::HollowCylinder::ComputeMomentOfInertia() {
    double I_center = mass * radius * radius;
    return I_center + mass * distance * distance;
}

void InertiaMomentCalculator::AddDisk(double mass, double radius, double distance) {
    shapes.push_back(new Disk(mass, radius, distance));
}

void InertiaMomentCalculator::AddHollowCylinder(double mass, double radius, double distance) {
    shapes.push_back(new HollowCylinder(mass, radius, distance));
}

double InertiaMomentCalculator::ComputeTotalMomentOfInertia() {
    double I = 0;
    for (auto shape : shapes) {
        I += shape->ComputeMomentOfInertia();
    }
    return I;
}

InertiaMomentCalculator::~InertiaMomentCalculator() {
    for (auto shape : shapes) {
        delete shape;
    }
}
