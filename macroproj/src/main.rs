use macroquad::prelude::*;

pub mod objs;
use objs::base::*;
use objs::load::*;

#[macroquad::main("Hi")]
async fn main() {
	let mut objs = load_all();
  loop {
    clear_background(BLACK);
    
		objs[0].draw(0.0, 0.0).await;
    next_frame().await;
  }
}
