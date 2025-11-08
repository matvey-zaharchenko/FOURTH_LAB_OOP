#include "include/figure.h"
#include "include/triangle.h"
#include "include/rectangle.h"
#include "include/square.h"
#include "include/array.h"

template<typename FigureType>
void print_figures_info(Array<std::shared_ptr<FigureType>>& figures) {
    if (figures.getsize() == 0) {
        std::cout << "Array is empty. Use command 1" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < figures.getsize(); ++i) {
        std::cout << "Figure " << i + 1 << ":" << std::endl;
        std::cout << *figures[i];
        figures[i]->printGeomCentre(std::cout);
        figures[i]->printArea(std::cout);
        std::cout << "-----------------" << std::endl;
    }
}

int main() {
    std::cout << "Action List:" << std::endl;
    std::cout << "1. Input figure" << std::endl;
    std::cout << "2. Print data of figure" << std::endl;
    std::cout << "3. Calculate sum of area of figure" << std::endl;
    std::cout << "4. Delete figure from array" << std::endl;
    std::cout << "5. Print info about triangle" << std::endl;
    std::cout << "6. Print info about rectangle" << std::endl;
    std::cout << "7. Print info about square" << std::endl;
    std::cout << "0. Quit" << std::endl;

    char c;
    int figureType;
    
    Array<std::shared_ptr<Figure<double>>> figures;
    Array<std::shared_ptr<Triangle<double>>> triangles;
    Array<std::shared_ptr<Rectangle<double>>> rectangles;
    Array<std::shared_ptr<Square<double>>> squares;

    while(true) {
        std::cin >> c;
        if(c == '0') {
            break;
        } else if(c == '1') {
            std::cout << "Input 1 for triangle | 2 for rectangle | 3 for square" << std::endl;
            std::cin >> figureType;

            if(figureType == 1) {
                std::cout << "Input 3 peaks coordinates (x y): " << std::endl;
                std::vector<double> xCoords, yCoords;
                for(int i = 0; i < 3; ++i) {
                    double x, y;
                    std::cin >> x >> y;
                    xCoords.push_back(x);
                    yCoords.push_back(y);
                }
                auto inputTriangle = std::make_shared<Triangle<double>>(3, xCoords, yCoords);
                figures.push_back(inputTriangle);
                triangles.push_back(inputTriangle);
            } else if(figureType == 2) {
                std::cout << "Input 4 peaks coordinates (x y): " << std::endl;
                std::vector<double> xCoords, yCoords;
                for(int i = 0; i < 4; ++i) {
                    double x, y;
                    std::cin >> x >> y;
                    xCoords.push_back(x);
                    yCoords.push_back(y);
                }
                auto inputRectangle = std::make_shared<Rectangle<double>>(4, xCoords, yCoords);
                figures.push_back(inputRectangle);
                rectangles.push_back(inputRectangle);
            } else if(figureType == 3) {
                std::cout << "Input 4 peaks coordinates (x y): " << std::endl;
                std::vector<double> xCoords, yCoords;
                for(int i = 0; i < 4; ++i) {
                    double x, y;
                    std::cin >> x >> y;
                    xCoords.push_back(x);
                    yCoords.push_back(y);
                }
                auto inputSquare = std::make_shared<Square<double>>(4, xCoords, yCoords);
                figures.push_back(inputSquare);
                squares.push_back(inputSquare);
            } else {
                std::cout << "Incorrect type of figure. Try again" << std::endl;
                continue;
            }
            std::cout << "Figure added. Input next command" << std::endl;
        } else if(c == '2') {
            print_figures_info(figures);
        } else if(c == '3') {
            if (figures.getsize() == 0) {
                std::cout << "Array is empty. Use command 1" << std::endl;
                continue;
            }
            
            double sum = 0;
            for(size_t i = 0; i < figures.getsize(); ++i) {
                sum += static_cast<double>(*figures[i]);
            }
            std::cout << "Sum of areas: " << sum << std::endl;
            std::cout << "Input next command" << std::endl;
        } else if(c == '4') {
            if (figures.getsize() == 0) {
                std::cout << "Array is empty. Use command 1" << std::endl;
                continue;
            }
            
            size_t index;
            std::cout << "Input index: ";
            std::cin >> index;
            
            while(index >= figures.getsize()) {
                std::cout << "Index out of range. Try again ";
                std::cin >> index;
            }
            
            figures.remove(index);
            std::cout << "Done. Input next command" << std::endl;   
        } else if(c == '5'){
            if(triangles.getsize() == 0){
                std::cout << "Triangles is empty\n";
            } else{
                print_figures_info(triangles); 
                std::cout << "Done. Input next command" << std::endl; 
                
            }
        } else if(c == '6'){
            if(triangles.getsize() == 0){
                std::cout << "Triangles is empty\n";
            } else{
                print_figures_info(rectangles); 
                std::cout << "Done. Input next command" << std::endl; 
                
            }
        }else if(c == '7'){
            if(triangles.getsize() == 0){
                std::cout << "Triangles is empty\n";
            } else{
                print_figures_info(squares); 
                std::cout << "Done. Input next command" << std::endl; 
            }
        }else {
            std::cout << "Incorrect number of command. Try again" << std::endl;
            continue;
        }
    }

    return 0;   
}