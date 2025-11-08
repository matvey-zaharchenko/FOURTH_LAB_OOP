#pragma once

#include <iostream>
#include "point.h"
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
#include <cmath>

template<Scalar T>
class Figure {
protected:
    using PointPtr = std::unique_ptr<Point<T>>;

    size_t numberOfPeaks;
    Point<T> geometric_centre;
    
    std::vector<PointPtr> peaks_coord;
    std::vector<T> sidesLen;

    void lenOfSidesCalc(const std::vector<PointPtr>& peaks) {
        size_t len = peaks.size();
        T x1, x2, y1, y2;
        T size;

        for(size_t i = 1; i < len; ++i) {
            x1 = peaks[i-1]->get_x(); y1 = peaks[i-1]->get_y();
            x2 = peaks[i]->get_x(); y2 = peaks[i]->get_y();
            
            size = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
            if(fabs(size) < 1e-12) {
                throw std::logic_error("Length of side can't be zero");
            }
            sidesLen.push_back(size);
        }
        x1 = peaks[len-1]->get_x(); y1 = peaks[len-1]->get_y();
        x2 = peaks[0]->get_x(); y2 = peaks[0]->get_y();
        size = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        if(fabs(size) < 1e-12) {
            throw std::logic_error("Length of side can't be zero");
        }
        sidesLen.push_back(size);
    }

public:
    Figure() : numberOfPeaks(3), geometric_centre(0, 0) {
        peaks_coord.push_back(std::make_unique<Point<T>>(0, 0));
        peaks_coord.push_back(std::make_unique<Point<T>>(0, 1));
        peaks_coord.push_back(std::make_unique<Point<T>>(1, 1));
        lenOfSidesCalc(peaks_coord);
    }

    Figure(int count, std::vector<T> xCoord, std::vector<T> yCoord) {
        size_t xSize = xCoord.size();
        size_t ySize = yCoord.size();

        if(count != (int)xSize || count != (int)ySize) {
            throw std::logic_error("Not enough or too many coordinates");
        } else if(count <= 2) {
            throw std::logic_error("Figure must have 3 or more peaks");
        } else if(xSize != ySize) {
            throw std::logic_error("X coordinates must be equal Y coordinates");
        }

        this->numberOfPeaks = count;
        for(size_t i = 0; i < count; ++i) {
            PointPtr cur_peak_ptr = std::make_unique<Point<T>>(xCoord[i], yCoord[i]);
            this->peaks_coord.push_back(std::move(cur_peak_ptr));
        }
        lenOfSidesCalc(peaks_coord);
    }

    Figure(const std::initializer_list<std::pair<T, T>>& initialValues) {
        size_t len = initialValues.size();
        if(len <= 2) {
            throw std::logic_error("Figure must have 3 or more peaks");
        }
        this->numberOfPeaks = len;

        for(const auto& val : initialValues) {
            this->peaks_coord.push_back(std::make_unique<Point<T>>(val.first, val.second));
        }
        lenOfSidesCalc(this->peaks_coord);
    }

    Figure(const Figure& other) {
        this->numberOfPeaks = other.numberOfPeaks;
        this->geometric_centre = other.geometric_centre;
        this->sidesLen = other.sidesLen;
        for(const auto& ptr : other.peaks_coord) {
            this->peaks_coord.push_back(std::make_unique<Point<T>>(ptr->get_x(), ptr->get_y()));
        }
    }

    Figure(Figure&& other) noexcept {
        this->numberOfPeaks = other.numberOfPeaks;
        this->geometric_centre = std::move(other.geometric_centre);
        this->sidesLen = std::move(other.sidesLen);
        this->peaks_coord = std::move(other.peaks_coord);
        other.numberOfPeaks = 0;
    }

    virtual void geometric_centre_calc() {return;};
    
    size_t getNumOfPeaks() const { return numberOfPeaks; }
    Point<T> getGeomCentre() const { return geometric_centre; }
    const std::vector<PointPtr>& getPeaks() const { return peaks_coord; }
    const std::vector<T>& getSides() const { return sidesLen; }

    void printGeomCentre(std::ostream& OutputStream) const {
        OutputStream << "Geometric centre: ";
        OutputStream << "x = " << geometric_centre.get_x() << " y = " << geometric_centre.get_y();
        OutputStream << std::endl;
    }

    void printArea(std::ostream& OutputStream) const {
        OutputStream << "Area: ";
        OutputStream << static_cast<double>(*this);
        OutputStream << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        int index = 1;
        for(const auto& elem : fig.peaks_coord) {
            os << "Peak " << index << " coordinates: " << "x = " << elem->get_x() 
               << " y = " << elem->get_y() << std::endl;
            ++index;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        for(size_t i = 0; i < fig.numberOfPeaks; ++i) {
            std::cout << "Input peak coordinate (x y): ";
            T x, y;
            is >> x >> y;
            fig.peaks_coord[i] = std::make_unique<Point<T>>(x, y);
        }
        
        fig.sidesLen.clear();
        fig.lenOfSidesCalc(fig.peaks_coord);
        fig.geometric_centre_calc();
        return is;
    }

    virtual operator double() const {return 0.0;}
    
    virtual bool operator==(const Figure<T>& other) const {return true;}
    virtual Figure& operator=(const Figure& other) { return *this; } 
    virtual Figure& operator=(Figure&& other) noexcept { return *this; } 
    
    virtual ~Figure() = default;
};