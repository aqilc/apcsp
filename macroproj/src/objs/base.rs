use macroquad::prelude::*;
use futures::try_join;

#[derive(Clone, Copy)]
pub enum Direction {
  N = 0, W = 1, E = 2, S = 3
}

pub struct Object {
  pub img: String,
  pub dir: Direction,
  pub loaded: bool,
  pub textures: [Texture2D; 4]
}

impl Object {
  pub async fn load(name: &str) -> Self {
    let textures = try_join!(
      load_texture(name),
      load_texture(name),
      load_texture(name),
      load_texture(name),
    ).unwrap();
    return Object {
      dir: Direction::N,
      img: name.to_string(),
      loaded: true,
      textures: [textures.0, textures.1, textures.2, textures.3]
    }
  }
  pub fn draw(&self, x: f32, y: f32) {
      draw_texture(self.textures[self.dir], x, y, WHITE);
  }
  pub fn up(&mut self) { self.dir = Direction::N; }
  pub fn down(&mut self) { self.dir = Direction::S; }
  pub fn left(&mut self) { self.dir = Direction::E; }
  pub fn right(&mut self) { self.dir = Direction::W; }
}
