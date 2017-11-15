#include <CGAL/Cartesian.h>
#include <iostream>
#include <vector>

#ifndef CGAL_USE_GEOMVIEW
int main()
  3{
  std::cout << "Geomview doesn't work on Windows, so..." << std::endl;
  return 0;
}
#else

#include <fstream>
#include <unistd.h> // for sleep()

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Projection_traits_xy_3.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>



typedef CGAL::Cartesian<double> K;

typedef K::Point_2 Point2;
typedef CGAL::Projection_traits_xy_3<K> Gt3;
typedef Gt3::Point Point3;

typedef CGAL::Delaunay_triangulation_2<K> Delaunay;

// loads an array of points from a file
std::vector<Point2> load_from_file(const char* file)
{
  std::vector<Point2> points;
  std::ifstream iFile(file, std::ios::in);

  Point3 p;
  while(iFile >> p) {
    points.push_back(Point2(p.x(), p.y()));
  }

  return points;
}

// Returns the contour polygons generated from the Delaunay
void generate_contour_line(float height, Delaunay D)
{
  return;
}

CGAL::Geomview_stream setup_geomview()
{
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-100, -100, -100, 600, 600, 600));
  gv.set_line_width(4);
  //gv.set_trace(true);
  gv.set_bg_color(CGAL::Color(0, 200, 200));
  // gv.clear();

  return gv;
}

int main()
{
  CGAL::Geomview_stream gv = setup_geomview();

  std::vector<Point2> points = load_from_file("data/points3");
  Delaunay D;

  for(Point2 p : points)
    D.insert(p);

  gv << CGAL::BLUE;
  std::cout << "Drawing 2D Delaunay triangulation in wired mode.\n";
  gv.set_wired(true);
  gv << D;

  std::cout << "Enter a key to finish" << std::endl;
  char ch;
  std::cin >> ch;

  return 0;
}
#endif
