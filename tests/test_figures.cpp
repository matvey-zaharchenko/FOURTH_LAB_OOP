#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "point.h"
#include "figure.h"
#include "triangle.h"
#include "rectangle.h"
#include "square.h"
#include "array.h"

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.get_x(), 0);
    EXPECT_EQ(p.get_y(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 2.7);
    EXPECT_DOUBLE_EQ(p.get_x(), 3.5);
    EXPECT_DOUBLE_EQ(p.get_y(), 2.7);
}

TEST(PointTest, Setters) {
    Point<float> p;
    p.set_x(1.5f);
    p.set_y(2.5f);
    EXPECT_FLOAT_EQ(p.get_x(), 1.5f);
    EXPECT_FLOAT_EQ(p.get_y(), 2.5f);
}

TEST(FigureTest, DefaultConstructor) {
    Figure<double> fig;
    EXPECT_EQ(fig.getNumOfPeaks(), 3);
}

TEST(FigureTest, ParameterizedConstructor) {
    std::vector<double> x = {0, 1, 0};
    std::vector<double> y = {0, 0, 1};
    
    Figure<double> fig(3, x, y);
    EXPECT_EQ(fig.getNumOfPeaks(), 3);
}

TEST(FigureTest, ParameterizedConstructorInvalidCount) {
    std::vector<double> x = {0, 1};
    std::vector<double> y = {0, 1};
    
    EXPECT_THROW(Figure<double>(2, x, y), std::logic_error);
}

TEST(FigureTest, CopyConstructor) {
    Figure<double> fig1;
    Figure<double> fig2(fig1);
    
    EXPECT_EQ(fig1.getNumOfPeaks(), fig2.getNumOfPeaks());
}

TEST(FigureTest, MoveConstructor) {
    Figure<double> fig1;
    Figure<double> fig2(std::move(fig1));
    
    EXPECT_EQ(fig2.getNumOfPeaks(), 3);
}

TEST(TriangleTest, DefaultConstructor) {
    Triangle<double> tri;
    EXPECT_EQ(tri.getNumOfPeaks(), 3);
}

TEST(TriangleTest, ParameterizedConstructor) {
    std::vector<double> x = {0, 3, 1.5};
    std::vector<double> y = {0, 0, 2.598};
    
    Triangle<double> tri(3, x, y);
    EXPECT_EQ(tri.getNumOfPeaks(), 3);
}

TEST(TriangleTest, ParameterizedConstructorInvalidCount) {
    std::vector<double> x = {0, 1, 2, 3};
    std::vector<double> y = {0, 1, 2, 3};
    
    EXPECT_THROW(Triangle<double>(4, x, y), std::logic_error);
}

TEST(TriangleTest, GeometricCentreCalculation) {
    Triangle<double> tri;
    tri.geometric_centre_calc();
    auto center = tri.getGeomCentre();
    
    EXPECT_NEAR(center.get_x(), 0.333, 0.001);
    EXPECT_NEAR(center.get_y(), 0.666, 0.001);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle<double> tri;
    double area = static_cast<double>(tri);
    
    EXPECT_NEAR(area, 0.5, 0.001);
}

TEST(TriangleTest, EqualityOperator) {
    Triangle<double> tri1;
    Triangle<double> tri2;
    
    EXPECT_TRUE(tri1 == tri2);
}

TEST(TriangleTest, CopyAssignment) {
    Triangle<double> tri1;
    Triangle<double> tri2;
    tri2 = tri1;
    
    EXPECT_TRUE(tri1 == tri2);
}

TEST(SquareTest, DefaultConstructor) {
    Square<double> sq;
    EXPECT_EQ(sq.getNumOfPeaks(), 4);
}

TEST(SquareTest, AreaCalculation) {
    Square<double> sq;
    double area = static_cast<double>(sq);
    
    EXPECT_NEAR(area, 1.0, 0.001);
}

TEST(SquareTest, GeometricCentreCalculation) {
    Square<double> sq;
    sq.geometric_centre_calc();
    auto center = sq.getGeomCentre();
    
    EXPECT_NEAR(center.get_x(), 0.5, 0.001);
    EXPECT_NEAR(center.get_y(), 0.5, 0.001);
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> rect;
    EXPECT_EQ(rect.getNumOfPeaks(), 4);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<double> rect;
    double area = static_cast<double>(rect);
    

    EXPECT_NEAR(area, 6.0, 0.001);
}


TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.getsize(), 0);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr.getsize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, Remove) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.remove(1);
    
    EXPECT_EQ(arr.getsize(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    
    Array<int> arr2(arr1);
    
    EXPECT_EQ(arr1.getsize(), arr2.getsize());
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    
    Array<int> arr2(std::move(arr1));
    
    EXPECT_EQ(arr2.getsize(), 2);
    EXPECT_EQ(arr1.getsize(), 0); 
}


TEST(SmartPointerTest, FigurePolymorphism) {
    std::shared_ptr<Figure<double>> fig = std::make_shared<Triangle<double>>();
    EXPECT_EQ(fig->getNumOfPeaks(), 3);
    
    fig = std::make_shared<Square<double>>();
    EXPECT_EQ(fig->getNumOfPeaks(), 4);
}

TEST(SmartPointerTest, ArrayWithSharedPtr) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Triangle<double>>());
    figures.push_back(std::make_shared<Square<double>>());
    
    EXPECT_EQ(figures.getsize(), 2);
    EXPECT_EQ(figures[0]->getNumOfPeaks(), 3);
    EXPECT_EQ(figures[1]->getNumOfPeaks(), 4);
}

TEST(ConceptTest, ScalarConstraint) {
    Point<int> p1;
    Point<double> p2;
    Point<float> p3;
    
}


TEST(ExceptionTest, InvalidFigureCreation) {
    std::vector<double> x = {0, 1}; 
    std::vector<double> y = {0, 1};
    
    EXPECT_THROW(Figure<double>(2, x, y), std::logic_error);
}

TEST(ExceptionTest, InvalidTriangleCreation) {
    std::vector<double> x = {0, 1, 2, 3}; 
    std::vector<double> y = {0, 1, 2, 3};
    
    EXPECT_THROW(Triangle<double>(4, x, y), std::logic_error);
}


TEST(IntegrationTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<Triangle<double>>());
    figures.push_back(std::make_shared<Square<double>>());
    
    double total_area = 0;
    for (size_t i = 0; i < figures.getsize(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }
    
    
    EXPECT_NEAR(total_area, 1.5, 0.001);
}

TEST(IntegrationTest, MixedArrays) {
    Array<std::shared_ptr<Triangle<double>>> triangles;
    Array<std::shared_ptr<Square<double>>> squares;
    
    triangles.push_back(std::make_shared<Triangle<double>>());
    squares.push_back(std::make_shared<Square<double>>());
    
    EXPECT_EQ(triangles.getsize(), 1);
    EXPECT_EQ(squares.getsize(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}