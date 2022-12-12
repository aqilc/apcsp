use macroquad::prelude::*;

pub mod objs;

#[macroquad::main("Hi")]
async fn main() {
  loop {

    next_frame().await;
  }
}
