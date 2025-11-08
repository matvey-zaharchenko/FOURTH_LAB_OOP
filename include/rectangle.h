#pragma once

#include "figure.h"

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    Rectangle() : Figure<T>() {
        this->numberOfPeaks = 4;
        this->peaks_coord.clear();
        this->peaks_coord.push_back(std::make_unique<Point<T>>(0, 0));
        this->peaks_coord.push_back(std::make_unique<Point<T>>(0, 2));
        this->peaks_coord.push_back(std::make_unique<Point<T>>(3, 2));
        this->peaks_coord.push_back(std::make_unique<Point<T>>(3, 0));
        this->lenOfSidesCalc(this->peaks_coord);
        this->geometric_centre_calc();
    }

    Rectangle(int count, std::vector<T> xCoord, std::vector<T> yCoord) : Figure<T>(count, xCoord, yCoord) {
        if(count != 4) {
            throw std::logic_error("Rectangle have 4 sides");
        }
        this->geometric_centre_calc();
    }

    Rectangle(const std::initializer_list<std::pair<T, T>>& initialValues) : Figure<T>(initialValues) {
        if(initialValues.size() != 4) {
            throw std::logic_error("Rectangle have 4 sides");
        }
        this->geometric_centre_calc();
    }

    Rectangle(const Rectangle& other) : Figure<T>(other) {}

    Rectangle(Rectangle&& other) noexcept : Figure<T>(std::move(other)) {} 

    void geometric_centre_calc() override {
        T x_sum = 0, y_sum = 0;
        for(const auto& point : this->peaks_coord) {
            x_sum += point->get_x();
            y_sum += point->get_y();
        }
        this->geometric_centre.set_x(x_sum / 4.0);
        this->geometric_centre.set_y(y_sum / 4.0);
    }

    operator double() const override {
        T x1, x2, x3, x4, y1, y2, y3, y4;
        x1 = this->peaks_coord[0]->get_x(); 
        x2 = this->peaks_coord[1]->get_x(); 
        x3 = this->peaks_coord[2]->get_x();
        x4 = this->peaks_coord[3]->get_x();
        y1 = this->peaks_coord[0]->get_y(); 
        y2 = this->peaks_coord[1]->get_y(); 
        y3 = this->peaks_coord[2]->get_y();
        y4 = this->peaks_coord[3]->get_y(); 
        T sum_1 = (x1*y2)+(x2*y3)+(x3*y4)+(x4*y1);
        T sum_2 = (y1*x2)+(y2*x3)+(y3*x4)+(y4*x1);
        T area = 0.5 * fabs(sum_1 - sum_2);
        return area;
    }

    bool operator==(const Figure<T>& other) const override {
        const Rectangle* otherRect = dynamic_cast<const Rectangle*>(&other);
        if(!otherRect) return false;
        
        std::vector<T> cpyThis = this->sidesLen;
        std::vector<T> cpyOther = otherRect->sidesLen;

        std::sort(cpyThis.begin(), cpyThis.end());
        std::sort(cpyOther.begin(), cpyOther.end());

        for(size_t i = 0; i < 4; ++i) {
            if(fabs(cpyThis[i] - cpyOther[i]) > 1e-12) {
                return false;
            }
        }
        return true;
    }

    Rectangle& operator=(const Rectangle& other) {
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

    Rectangle& operator=(Rectangle&& other) noexcept {
        if(this != &other) {
            this->numberOfPeaks = std::move(other.numberOfPeaks);
            this->sidesLen = std::move(other.sidesLen);
            this->geometric_centre = std::move(other.geometric_centre);
            this->peaks_coord = std::move(other.peaks_coord);
        }
        return *this;
    }
};