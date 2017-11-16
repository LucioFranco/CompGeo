#include <CGAL/Cartesian.h>
#include <iostream>
#include <vector>

#ifndef CGAL_USE_GEOMVIEW
int main()
{
  std::cout << "Geomview doesn't work on Windows, so..." << std::endl;
  return 0;
}
#else

#include <fstream>
#include <unistd.h> // for sleep()

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Polygon_2.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>

typedef CGAL::Cartesian<double> K;

typedef K::Point_2 Point2;
typedef CGAL::Projection_traits_xy_3<K> Gt3;
typedef Gt3::Point Point3;
typedef CGAL::Polygon_2<K> Polygon;

typedef CGAL::Delaunay_triangulation_2<K> Delaunay;

typedef Polygon::Edge_const_iterator EdgeIterator;
typedef Polygon::Vertex_iterator VertexIterator;

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
std::vector<Polygon>  generate_contour_line(float height, Delaunay D)
{
  std::vector<Polygon> contours;

  return contours;
}

CGAL::Geomview_stream setup_geomview()
{
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-100, -100, -100, 600, 600, 600));
  gv.set_line_width(4);
  gv.set_vertex_radius(20);
  //gv.set_trace(true);
  gv.set_bg_color(CGAL::Color(0, 200, 200));
  // gv.clear();

  return gv;
}

void draw_polygon(CGAL::Geomview_stream& gv, Polygon p)
{
  gv << CGAL::RED;
  std::cout << "Drawing polygon" << std::endl;
  gv.set_wired(true);
  for (EdgeIterator ei = p.edges_begin(); ei != p.edges_end(); ++ei)
    gv << *ei;
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

  Polygon p;

  p.push_back(points.at(0));
  p.push_back(points.at(1));
  p.push_back(points.at(2));
  p.push_back(points.at(3));

  sleep(5);
  draw_polygon(gv, p);

  std::cout << "Enter a key to finish" << std::endl;
  char ch;
  std::cin >> ch;

  return 0;
}
#endif
