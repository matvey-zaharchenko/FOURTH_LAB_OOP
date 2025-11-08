#pragma once

#include "figure.h"

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() : Figure<T>() {
        this->geometric_centre_calc();
    }

    Triangle(int count, std::vector<T> xCoord, std::vector<T> yCoord) : Figure<T>(count, xCoord, yCoord) {
        if(count != 3) {
            throw std::logic_error("Triangle have 3 sides");
        }
        this->geometric_centre_calc();
    }

    Triangle(const std::initializer_list<std::pair<T, T>>& initialValues) : Figure<T>(initialValues) {
        if(initialValues.size() != 3) {
            throw std::logic_error("Triangle have 3 sides");
        }
        this->geometric_centre_calc();
    }

    Triangle(const Triangle& other) : Figure<T>(other) {}

    Triangle(Triangle&& other) noexcept : Figure<T>(std::move(other)) {} 

    void geometric_centre_calc() override {
        T x1, x2, x3, y1, y2, y3;
        x1 = this->peaks_coord[0]->get_x(); 
        x2 = this->peaks_coord[1]->get_x(); 
        x3 = this->peaks_coord[2]->get_x();
        y1 = this->peaks_coord[0]->get_y(); 
        y2 = this->peaks_coord[1]->get_y(); 
        y3 = this->peaks_coord[2]->get_y(); 
        
        this->geometric_centre.set_x((x1 + x2 + x3) / 3.0);
        this->geometric_centre.set_y((y1 + y2 + y3) / 3.0);
    }

    operator double() const override {
        T x1, x2, x3, y1, y2, y3;
        x1 = this->peaks_coord[0]->get_x(); 
        x2 = this->peaks_coord[1]->get_x(); 
        x3 = this->peaks_coord[2]->get_x();
        y1 = this->peaks_coord[0]->get_y(); 
        y2 = this->peaks_coord[1]->get_y(); 
        y3 = this->peaks_coord[2]->get_y(); 
        
        T area = 0.5 * fabs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
        return area;
    }

    bool operator==(const Figure<T>& other) const override {
        const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
        if(!otherTriangle) return false;
        
        std::vector<T> cpyThis = this->sidesLen;
        std::vector<T> cpyOther = otherTriangle->sidesLen;

        std::sort(cpyThis.begin(), cpyThis.end());
        std::sort(cpyOther.begin(), cpyOther.end());

        for(size_t i = 0; i < 3; ++i) {
            if(fabs(cpyThis[i] - cpyOther[i]) > 1e-12) {
                return false;
            }
        }
        return true;
    }

    Triangle& operator=(const Triangle& other) {
        if(this != &other) {
            this->numberOfPeaks = other.numberOfPeaks;
            this->sidesLen = other.sidesLen;
            this->geometric_centre = other.geometric_centre;
        
            this->peaks_coord.clear();
            for(const auto& ptr : other.peaks_coord) {
                this->peaks_coord.push_back(std::make_unique<Point<T>>(ptr->get_x(), ptr->get_y()));
            }
        }
        return *this;
    }

    Triangle& operator=(Triangle&& other) noexcept {
        if(this != &other) {
            this->numberOfPeaks = std::move(other.numberOfPeaks);
            this->sidesLen = std::move(other.sidesLen);
            this->geometric_centre = std::move(other.geometric_centre);
            this->peaks_coord = std::move(other.peaks_coord);
        }
        return *this;
    }
};