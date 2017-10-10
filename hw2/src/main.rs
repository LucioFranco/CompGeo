// Sam Windham, Lucio Franco

mod poly;
use poly::poly::cross;
use poly::poly::Polygon;

fn left_tangent(poly: Polygon, q: (f32, f32)) -> f32 {
    for i in 0..poly.n {
        let current = poly.points[i as usize];
        let next = poly.points[((i + 1) % poly.n) as usize];
        let cross = cross(current, next);

        println!("{}", cross);
    }

    return 0.0;
}

fn main() {

    let poly = Polygon {
        n: 3,
        points: vec![(1.0, 1.0), (3.0, 1.0), (1.0, 3.0)],
    };

    let origin = (0.0, 0.0);

    let result: f32 = left_tangent(poly, origin);
    println!("Left Tangent: {}", result);
}
