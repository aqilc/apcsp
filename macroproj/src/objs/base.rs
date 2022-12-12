#[derive(Clone, Copy)]
#[repr(u8)]
pub enum Direction {
  N = b'N', W = b'W', E = b'E', S = b'S'
}

pub struct Object<'a> {
  pub dir: Direction,
  pub img: &'a str,
  pub loaded: bool
}

impl<'a> Object<'a> {
  pub fn load(file: &str) {
    
    return Object {
      dir: Direction::N,
      img: file,
      loaded: true
    }
  }
}