#![allow(dead_code)]
pub mod util {
    pub struct Polygon {
        pub n: u64,
        pub points: Vec<(f64, f64)>,
    }

    pub fn cross((x1, y1): (f64, f64), (x2, y2): (f64, f64)) -> f64 {
        (x1 * y2) - (x2 * y1)
    }

    pub fn is_left((p0x, p0y): (f64, f64), (p1x, p1y): (f64, f64), (qx, qy): (f64, f64)) -> bool {
        // p0 = poly[i]
        // p1 = poly[i+1]
        // v1 = p1 - p0
        // v2 = p0 - q
        // left = cross(v2, v1) > 0
        // left = cross((p0 - q),(p1 - p0)) > 0

        cross((p0x - qx, p0y - qy), (p1x - p0x, p1y - p0y)) > 0.
    }

    pub fn is_right((p0x, p0y): (f64, f64), (p1x, p1y): (f64, f64), (qx, qy): (f64, f64)) -> bool {
        !is_left((p0x, p0y), (p1x, p1y), (qx, qy))
    }
}
