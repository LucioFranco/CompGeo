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
#include <algorithm>
#include <tuple>

#include <CGAL/Triangulation_2.h>
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
typedef Delaunay::Vertex_handle Vertex_handle;
typedef Delaunay::Finite_faces_iterator Finite_faces_iterator;
typedef Delaunay::Face_circulator Face_circulator;
typedef Delaunay::Edge_circulator Edge_circulator;
typedef CGAL::Level_interval<Face_handle> Interval;
typedef CGAL::Interval_skip_list<Interval> Interval_skip_list;

typedef Polygon::Edge_const_iterator EdgeIterator;
typedef Polygon::Vertex_iterator VertexIterator;

// loads an array of points from a file
std::vector<Point3> load_from_file(const char* file)
{
  std::vector<Point3> points;
  std::ifstream iFile(file, std::ios::in);

  Point3 p;
  while(iFile >> p) {
    points.push_back(p);
  }

  return points;
}

// get containg edge (high, low)
std::pair<int,int> containing_edge(std::vector<double> vertices, int height)
{
  int high = 0, low = 0;

  if(vertices.size() == 2) {
    if(vertices[0] > vertices[1]) {
      high = 0;
      low  = 1;
    } else {
      high = 1;
      low = 0;
    }
  } else {
    for(int i = 0; i < vertices.size(); i++) {
      if (vertices[i] > height) {
        high = i;
      }
    }
    for(int i = 0; i < vertices.size(); i++) {
      if (vertices[i] > height && vertices[i] < vertices[high]) {
        high = i;
      }
    }
    for(int i = 0; i < vertices.size(); i++) {
      if (vertices[i] < height) {
        low = i;
      }
    }
    for(int i = 0; i < vertices.size(); i++) {
      if (vertices[i] < height && vertices[i] >= vertices[low]) {
        low = i;
      }
    }
  }

  return std::make_pair(high, low);
}

// Returns the contour polygons generated from the Delaunay
std::vector<Polygon> generate_contour_line(float height, Delaunay D)
{
  std::vector<Polygon> contours;

  // Build interval skip list
  Interval_skip_list isl;
  std::vector<Interval> intervals;
  for(Finite_faces_iterator fh = D.finite_faces_begin();
      fh != D.finite_faces_end();
      ++fh) {
    Interval inter = Interval(fh);
    intervals.push_back(inter);
    isl.insert(inter);
  }

  // Find all faces at height
  std::list<Interval> level;
  isl.find_intervals(height, std::back_inserter(level));

  int i = 1;
  while(!level.empty() && i > 0) {
    Interval &interval = level.front();
    level.pop_front();

    Polygon poly;
    Face_handle fh = interval.face_handle();

    // Loop for the entire contour, stop if not in the level list
    // std::find

    Point3 *high;
    Point3 *low;

    int test_iterator = 100;
    while(test_iterator > 0) {
      if (&fh == NULL || fh->vertex(0) == D.infinite_face()->vertex(0)) {
        test_iterator--;
      } else {

        std::vector<double> heights;

        heights.push_back(fh->vertex(0)->point().z());
        heights.push_back(fh->vertex(1)->point().z());
        heights.push_back(fh->vertex(2)->point().z());

        std::pair<int,int> edge = containing_edge(heights, height);
        if(high && high == &fh->vertex(edge.first)->point() &&
           low == &fh->vertex(edge.second)->point()) {
          std::cout << "change" << std::endl;
          heights.erase(heights.begin() + edge.first);
          edge = containing_edge(heights, height);
        }
        high = &fh->vertex(edge.first)->point();
        low = &fh->vertex(edge.second)->point();


        //isl.remove(Interval(fh));

        int next_face = 3 - edge.first - edge.second;

        // --- Interpolate Contour Point ---
        // Weight is determined from the elevation(z-axis).
        // w = ( dist to new elevation ) / ( distance between p1 and p2 )
        // w = (height - p1.z) / (p2.z - p1.z)

        double w = (height - low->z()) / (high->z() - low->z());

        // Find x and y from weighted average along each axis
        // x = p1.x*(1 - w) + p2.x*(w)
        double x = low->x() * (1 - w) +
          high->x() * w;
        // y = p1.y*(1 - w) + p2.y*(w)
        double y = low->y() * (1 - w) +
          high->y() * w;

        poly.push_back(Point2(x,y));
        // --- End interpolate ---

        // Test output

        std::cout << "\n0: " << fh->vertex(0)->point() << std::endl;
        std::cout << "1: " << fh->vertex(1)->point() << std::endl;
        std::cout << "2: " << fh->vertex(2)->point() << std::endl;

        std::cout << "High: " << *high << ", low: " << *low << std::endl;
        std::cout << "Next Face: " << next_face << std::endl;


        fh = fh->neighbor(next_face);
        test_iterator--;
      }
    }

    contours.push_back(poly);

    i--;
  }

  return contours;
}

// Initialize Geomview settings and return Geomview_stream context
CGAL::Geomview_stream setup_geomview()
{
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-100, -100, -100, 600, 600, 600));
  gv.set_line_width(4);
  gv.set_vertex_radius(20);
  gv.set_bg_color(CGAL::Color(0, 200, 200));

  return gv;
}

// Draws Polygon_2 in a Geomview_stream context that is passed by ref
void draw_polygon(CGAL::Geomview_stream& gv, Polygon p)
{
  gv << CGAL::RED;
  
  gv.set_wired(true);

  // Iterate through the edges and display them
  for (EdgeIterator ei = p.edges_begin(); ei != p.edges_end(); ++ei) {
    std::cout << "edge: " <<  *ei << "\n" << std::endl;
    gv << *ei;
  }
}

int main()
{
  CGAL::Geomview_stream gv = setup_geomview();

  // format = point.x point.y point.z
  std::vector<Point3> points = load_from_file("data/points3");

  // Build delaunay triangulation from data points
  Delaunay D;
  for(Point3 p : points)
    D.insert(p);

  // Draw Delaunay in geomview
  
  gv << CGAL::BLUE;
  std::cout << "Drawing 2D Delaunay triangulation in wired mode.\n";
  gv.set_wired(true);
  gv << D;

  // Enter contour elevation query
  double elevation = 170.0;
  std::vector<Polygon> contours = generate_contour_line(elevation, D);

  for(Polygon polygon : contours) {
    draw_polygon(gv, polygon);
  }

  std::cout << "Enter a key to finish" << std::endl;
  char ch;
  std::cin >> ch;
  
  return 0;
}
#endif
