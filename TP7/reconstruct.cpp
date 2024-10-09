//You can use "cmake -DCGAL_DIR=$HOME/CGAL-5.4 -DCMAKE_BUILD_TYPE=Release ." in case if you don't have CGAL installed
//Have a look at "https://en.wikipedia.org/wiki/STL_(file_format)" for the syntax of STL file format (consider normal as 0,0,0)
//Use MeshLab software (https://www.meshlab.net/) to visualize the results incase you don't know how to render it

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include<iostream>
#include <fstream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_3<K> Delaunay;
typedef Delaunay::Point Point;

Delaunay T;

int main(int argc, char **argv)
{
    const char* fname =argv[1]; //Reading the filename from the arguments
    std::ifstream stream(fname); //Reading the file
    Point p;
    while(!stream.eof()) //While the file is completely read
    {
        stream>>p; //Save line by line (x,y,z coordinates) to a point variable
        T.insert(Point(p.x(),p.y(),p.z())); //Insert the point into incremental Delaunay construction
    }
    Delaunay::Finite_cells_iterator vit; //An iterator variable that can iterate over the Delaunay cells (tetrahedrons)
    for(vit=T.finite_cells_begin();vit!=T.finite_cells_end();vit++) //Do for each cell. T.finite_cells_begin() gives a starting tetrahedron, ++ moves to next tetrahedron, T.finite_cells_end() gives the final tetrahedron ** This loop is just to give an idea about how to access cells and vertices, it is not required in the program
    	std::cout<<vit->vertex(0)->point()<<" "<<vit->vertex(1)->point()<<" "<<vit->vertex(2)->point()<<" "<<vit->vertex(3)->point()<<"\n"; //Printing the vertex coordinates of 4 points of the tetrahedron
    //TODO: Apply Delaunay filtering (take each Delaunay face [have a look at Delaunay facets as well - https://doc.cgal.org/latest/Triangulation_3/index.html], and check whether it satisfies the requirement)
    //Hint: You can use CGAL::circumcenter() to compute the circumcenters of a Triangle/Cell
    //TODO: Save the result into an STL file
    return 1;
}
