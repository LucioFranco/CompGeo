// Sam Windham, Lucio Franco

mod poly;
use poly::poly::cross;
use poly::poly::Polygon;

fn left_tangent(poly: Polygon, q: (f32, f32)) -> f32 {
    for i in 0..poly.n {
        // current point
        let current = poly.points[i as usize];
        // next point
        let next = poly.points[((i + 1) % poly.n) as usize];

        // edge vector between current and next
        let edge_vec = (next.0 - current.0, next.1 - current.1);
        let q_vec = (current.0 - q.0, current.1 - q.1);

        let cross = cross(q_vec, edge_vec);

        println!(
            "({}, {})\t-> ({}, {}):\t{}",
            edge_vec.0,
            edge_vec.1,
            q_vec.0,
            q_vec.1,
            cross
        );
    }

    return 0.0;
}

fn main() {

    println!("\nRight-turn: <= 0");
    println!("Left-turn:  > 0\n");

    let poly = Polygon {
        n: 3,
        points: vec![(1.0, 1.0), (3.0, 1.0), (1.0, 3.0)],
    };

    let origin = (0.0, 0.0);

    let result: f32 = left_tangent(poly, origin);
    println!("Left Tangent: {}", result);
}
