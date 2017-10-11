// Sam Windham, Lucio Franco

mod poly;
use poly::poly::cross;
use poly::poly::Polygon;
use poly::poly::Vec2;

fn left_tangent(poly: Polygon, q: Vec2) -> f32 {
    let mut sign = false;

    for i in 0..poly.n {
        // current point
        let current: Vec2 = poly.points[i as usize] as Vec2;
        // next point
        let next: Vec2 = poly.points[((i + 1) % poly.n) as usize] as Vec2;

        // edge vector between current and next
        let edge_vec: Vec2 = next - current;
        let q_vec: Vec2 = current - q;

        let cross = cross(q_vec, edge_vec);

        sign = cross > 0.;

        println!(
            "q({}, {}) x e({}, {}):\t{}",
            q_vec.0,
            q_vec.1,
            edge_vec.0,
            edge_vec.1,
            if sign { "left" } else { "right" }
        );
    }

    0.
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
    println!("\nLeft Tangent: {}", result);
}
