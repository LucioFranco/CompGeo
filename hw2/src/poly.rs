pub mod poly {
    pub struct Polygon {
        pub n: u32,
        pub points: Vec<(f32, f32)>,
    }

    pub fn cross((x1, y1): (f32, f32), (x2, y2): (f32, f32)) -> f32 {
        return (x1 * y2) - (x2 * y1);
    }
}
