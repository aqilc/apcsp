use macroquad::prelude::*;
use futures::{
	future::join_all,
};

#[derive(Clone, Copy)]
pub enum Direction {
  E = 0, W = 1, N = 2, S = 3
}

pub struct Object {
  pub img: String,
  pub dir: Direction,
  pub loaded: bool,
  pub textures: [Option<Texture2D>; 4]
}

impl Object {
  pub fn new(name: &str) -> Self {
    return Object {
      dir: Direction::N,
      img: name.to_string(),
      loaded: true,
      textures: [None; 4]
    }
  }
  pub async fn draw(&mut self, x: f32, y: f32) {
		if self.textures[self.dir as usize].is_none() { self.load_side(self.dir).await }
    draw_texture(self.textures[self.dir as usize].unwrap(), x, y, WHITE);
  }
  pub fn up(&mut self) { self.dir = Direction::N; }
  pub fn down(&mut self) { self.dir = Direction::S; }
  pub fn left(&mut self) { self.dir = Direction::E; }
  pub fn right(&mut self) { self.dir = Direction::W; }

	pub async fn load_side(&mut self, dir: Direction) {
		match dir {
			Direction::E => {
				self.textures[0] = load_texture(&format!("./res/imgs/{}_E.png", &self.img)).await.ok()
      },
			Direction::W => {
				self.textures[1] = load_texture(&format!("./res/imgs/{}_W.png", &self.img)).await.ok()
      },
			Direction::N => {
				self.textures[2] = load_texture(&format!("./res/imgs/{}_N.png", &self.img)).await.ok()
      },
			Direction::S => {
				self.textures[3] = load_texture(&format!("./res/imgs/{}_S.png", &self.img)).await.ok()
      },
    }
  }
}

//pub async fn load_objs(list: Vec<&str>) -> Vec<Object> {
//	join_all(list.iter().map(|s| Object::load(s))).await
//}
