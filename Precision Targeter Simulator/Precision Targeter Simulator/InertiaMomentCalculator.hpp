/*
InertialMomentCalculator.hpp

This class is used to define the mass distribution of the rotating mechanism dynamically, as it may change as the prototype is iterated.
This class also allows automatic computing of the rotational moment of inertia, I, of the rotating mechanism given the mass distribution.

Three mass types are defined: disk mass and hollow cylinder mass.

For each struct, mass is the total mass of that chunk, and distance is the distance from the center of rotation to the center of mass of that chunk.
Other parameters are self-explanatory.
*/


#pragma once
#include <vector>

class InertiaMomentCalculator {
public:
    class Shape {
    public:
        double mass;
        double radius;
        double distance;

        Shape(double m, double r, double d);
        virtual double ComputeMomentOfInertia() = 0;
        virtual ~Shape();
    };

    class Disk : public Shape {
    public:
        Disk(double m, double r, double d);
        double ComputeMomentOfInertia() override;
    };

    class HollowCylinder : public Shape {
    public:
        HollowCylinder(double m, double r, double d);
        double ComputeMomentOfInertia() override;
    };

    std::vector<Shape*> shapes;

    void AddDisk(double mass, double radius, double distance);
    void AddHollowCylinder(double mass, double radius, double distance);
    double ComputeTotalMomentOfInertia();
    ~InertiaMomentCalculator();
};
