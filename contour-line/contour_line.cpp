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
#include <CGAL/Polygon_2.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>

#include <CGAL/Interval_skip_list.h>
#include <CGAL/Level_interval.h>


typedef CGAL::Cartesian<double> K;

typedef K::Point_2 Point2;
typedef CGAL::Projection_traits_xy_3<K> Gt;
typedef K::Point_3 Point3;
typedef CGAL::Polygon_2<K> Polygon;

typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;

typedef Delaunay::Face_handle Face_handle;
typedef Delaunay::Finite_faces_iterator Finite_faces_iterator;
typedef CGAL::Level_interval<Face_handle> Interval;
typedef CGAL::Interval_skip_list<Interval> Interval_skip_list;

// loads an array of points from a file
std::vector<Point3> load_from_file(const char* file)
{
  std::vector<Point3> points;
  std::ifstream iFile(file, std::ios::in);

  Point3 p;
  while(iFile >> p) {
    points.push_back(Point3(p.x(), p.y(), p.z()));
  }

  return points;
}

// Returns the contour polygons generated from the Delaunay
std::vector<Polygon> generate_contour_line(float height, Delaunay D)
{
  std::vector<Polygon> contours;

  // Build interval skip list
  Interval_skip_list isl;
  for(Finite_faces_iterator fh = D.finite_faces_begin();
      fh != D.finite_faces_end();
      ++fh) {
    isl.insert(Interval(fh));
  }

  // Find all faces at height
  std::list<Interval> level;
  isl.find_intervals(height, std::back_inserter(level));

  // Print list of faces at height
  for(std::list<Interval>::iterator it = level.begin();
      it != level.end();
      ++it) {
    std::cout << D.triangle(it->face_handle()) << std::endl;
  }
  
  return contours;
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

  std::vector<Point3> points = load_from_file("data/points3");
  Delaunay D;

  for(Point3 p : points)
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
