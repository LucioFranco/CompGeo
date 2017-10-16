// Sam Windham, Lucio Franco
mod util;
use util::util::{Polygon, is_left};

// returns index of left tangenet to point q
fn left_tangent(n: u64, p: &[(f64, f64)], q: (f64, f64)) -> u64 {
    // first point is the left tangent
    if is_left(q, p[(n - 1) as usize], p[0]) && !is_left(q, p[0], p[1]) {
        0
    } else {
        let mut i: u64 = 1;
        let mut offset: u64 = 1;
        loop {
            let prev = p[((i - 1) % n) as usize];
            let current = p[i as usize];
            let next = p[((i + 1) % n) as usize];

            let edge_dir = is_left(q, current, next);

            // current point is the tangent
            if is_left(q, prev, current) && !edge_dir {
                return i;
            }

            let prev_edge_dir = is_left(q, p[(i - offset) as usize], p[(i - offset + 1) as usize]);
            // current edge left
            if edge_dir {
                // prev edge left and current point right of prev point
                if prev_edge_dir && !is_left(q, p[(i - offset) as usize], current) {
                    i -= offset;
                    offset = 1;
                }
                // previous edge is right  OR  current edge left of previous edge
                else {
                    offset *= 2;
                }
            }
            // current edge is right
            else {
                // prev edge is left
                if prev_edge_dir {
                    i -= offset;
                    offset = 1;
                }
                // prev edge is right
                else {
                    offset *= 2;
                }
            }

            i = std::cmp::min(i + offset, n - 1);
        }
    }
}

fn main() {
    // q point
    let origin = (0.0, 0.0);

    // Left tangent = 2:(1, 3)
    let poly_small = Polygon {
        n: 3,
        points: vec![(1.0, 1.0), (3.0, 1.0), (1.0, 3.0)],
    };
    let mut result: u64 = left_tangent(poly_small.n, &poly_small.points, origin);
    assert!(poly_small.points[2] == poly_small.points[result as usize]);

    // Left tangent = 9:(1.25, 4.7)
    let poly_large = Polygon {
        n: 17,
        points: vec![
            (6.10, 2.29),
            (6.46, 3.22),
            (6.46, 4.22),
            (6.10, 5.15),
            (5.43, 5.89),
            (4.53, 6.34),
            (3.53, 6.43),
            (2.57, 6.16),
            (1.77, 5.55),
            (1.25, 4.70),
            (1.06, 3.72),
            (1.25, 2.74),
            (1.77, 1.89),
            (2.57, 1.28),
            (3.53, 1.01),
            (4.53, 1.10),
            (5.43, 1.55),
        ],
    };
    result = left_tangent(poly_large.n, &poly_large.points, origin);
    assert!(poly_large.points[9] == poly_large.points[result as usize]);

    println!("All tests passed!");
}
