use macroquad::prelude::*;

pub mod objs;

#[macroquad::main("Hi")]
async fn main() {
  loop {
    clear_background(BLACK);
    
    next_frame().await;
  }
}
