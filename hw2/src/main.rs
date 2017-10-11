// Sam Windham, Lucio Franco
mod util;
use util::util::{cross, Polygon};

fn left_tangent(poly: Polygon, q: (f32, f32)) -> (f32, f32) {
    let mut sign = false;
    let mut left_tan = (0., 0.);

    for i in 0..poly.n {
        // current point
        let current = poly.points[i as usize];
        // next poi nt
        let next = poly.points[((i + 1) % poly.n) as usize];

        // edge vector between current and next
        let edge_vec = (next.0 - current.0, next.1 - current.1);
        let q_vec = (current.0 - q.0, current.1 - q.1);

        let cross = cross(q_vec, edge_vec);

        if sign && (sign != (cross > 0.)) {
            left_tan = current;
        }

        sign = cross > 0.;

    }

    left_tan
}

fn main() {
    let poly = Polygon {
        n: 3,
        points: vec![(1.0, 1.0), (3.0, 1.0), (1.0, 3.0)],
    };

    let origin = (0.0, 0.0);

    let result: (f32, f32) = left_tangent(poly, origin);
    println!("\nLeft Tangent: ({},{})", result.0, result.1);
}
