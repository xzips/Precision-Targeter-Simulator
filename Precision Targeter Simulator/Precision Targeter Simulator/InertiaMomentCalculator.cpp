//InertialMomentCalculator.cpp, see InertialMomentCalculator.hpp for more info

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
