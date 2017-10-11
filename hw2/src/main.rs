// Sam Windham, Lucio Franco
mod util;
use util::util::{Polygon, is_left, is_right};

// returns index of left tangenet to point q
fn left_tangent(n: u64, p: Vec<(f64, f64)>, q: (f64, f64)) -> u64 {

    // above = left
    // below = right


    // test if first point is left tangent
    if is_right(p[0], p[1], q) && is_left(p[(n - 1) as usize], p[0], q) {
        return 0;
    }
    for i in 1..n {
        // previous point
        let prev = p[(i - 1) as usize];
        // current point
        let current = p[i as usize];

        let left = is_left(prev, current, q);

        println!("{} - ({}, {}): {}", i, current.0, current.1, left);
    }

    (n - 1) as u64

}

fn main() {
    // q point
    let origin = (0.0, 0.0);

    // Left tangent = (1, 3)
    //let poly_small = Polygon {
    //    n: 3,
    //    points: vec![(1.0, 1.0), (3.0, 1.0), (1.0, 3.0)],
    // };
    //let mut result: (f64, f64) = left_tangent(poly_small, origin);
    //let mut correct: (f64, f64) = (1.0, 3.0);
    //assert!(result.0 - correct.0 <= 0.000000000001 && result.1 - correct.0 <= 0.000000000001);

    // Left tangent = 9:(1.25, 4.7)
    let poly_large = Polygon {
        n: 17,
        points: vec![
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
            (6.10, 2.29),
        ],
    };
    let result: u64 = left_tangent(poly_large.n, poly_large.points, origin);
    //let correct: (f64, f64) = (1.25, 4.70);
    println!("({})", result);
    //assert!(result.0 - correct.0 <= 0.000000000001 && result.1 - correct.0 <= 0.000000000001);

}
