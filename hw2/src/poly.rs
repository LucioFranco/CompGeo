pub mod poly {
    use std::ops::Sub;

    pub struct Vec2(pub f32, pub f32);

    impl Sub for Vec2 {
        type Output = Vec2;

        fn sub(self, other: Vec2) -> Vec2 {
            Vec2(self.0 - other.0, self.1 - other.1)
        }
    }

    pub struct Polygon {
        pub n: u32,
        pub points: Vec<Vec2>,
    }

    pub fn cross((x1, y1): Vec2, (x2, y2): Vec2) -> f32 {
        return (x1 * y2) - (x2 * y1);
    }
}
