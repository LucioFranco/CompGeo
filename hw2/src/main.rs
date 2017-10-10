// Sam Windham, Lucio Franco

mod poly;

fn main() {
    use poly::poly::cross;

    let result = cross((1.0, 2.0), (3.0, 4.0));
    println!("{}", result);
}
