#pragma once

#include "figure.h"

template <Scalar T>
class Square : public Figure<T> {
public:
    Square() : Figure<T>() {
        this->numberOfPeaks = 4;
        this->peaks_coord.clear();
        this->peaks_coord.push_back(std::make_unique<Point<T>>(0, 0));
        this->peaks_coord.push_back(std::make_unique<Point<T>>(0, 1));
        this->peaks_coord.push_back(std::make_unique<Point<T>>(1, 1));
        this->peaks_coord.push_back(std::make_unique<Point<T>>(1, 0));
        this->lenOfSidesCalc(this->peaks_coord);
        this->geometric_centre_calc();
    }

    Square(int count, std::vector<T> xCoord, std::vector<T> yCoord) : Figure<T>(count, xCoord, yCoord) {
        if(count != 4) {
            throw std::logic_error("Square have 4 sides");
        }
        this->geometric_centre_calc();
    }

    Square(const std::initializer_list<std::pair<T, T>>& initialValues) : Figure<T>(initialValues) {
        if(initialValues.size() != 4) {
            throw std::logic_error("Square have 4 sides");
        }
        this->geometric_centre_calc();
    }

    Square(const Square& other) : Figure<T>(other) {}

    Square(Square&& other) noexcept : Figure<T>(std::move(other)) {} 

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
        if(this->sidesLen.empty()) return 0;
        return this->sidesLen[0] * this->sidesLen[0];
    }

    bool operator==(const Figure<T>& other) const override {
        const Square* otherSquare = dynamic_cast<const Square*>(&other);
        if(!otherSquare) return false;
        return this->sidesLen == otherSquare->sidesLen;
    }

    Square& operator=(const Square& other) {
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

    Square& operator=(Square&& other) noexcept {
        if(this != &other) {
            this->numberOfPeaks = std::move(other.numberOfPeaks);
            this->sidesLen = std::move(other.sidesLen);
            this->geometric_centre = std::move(other.geometric_centre);
            this->peaks_coord = std::move(other.peaks_coord);
        }
        return *this;
    }
};