#![allow(dead_code)]

use rktor::core;
use winit;
use winit::{
    event::{Event, WindowEvent},
    event_loop::{ControlFlow, EventLoop, EventLoopWindowTarget},
    keyboard::{Key, NamedKey},
    window::{Window, WindowBuilder},
};

const WINDOW_TITLE: &'static str = "erktor";
const WINDOW_WIDTH: u32 = 640;
const WINDOW_HEIGHT: u32 = 360;

struct App {
    win: Window,
}

impl App {
    fn new(evt_loop: &EventLoop<()>) -> Self {
        let win = WindowBuilder::new()
            .with_title(WINDOW_TITLE)
            .with_inner_size(winit::dpi::LogicalSize::new(WINDOW_WIDTH, WINDOW_HEIGHT))
            .build(&evt_loop)
            .expect("Failed to create window");
        App { win }
    }

    fn handle_keys(&self, key: Key, elwt: &EventLoopWindowTarget<()>) {
        match key {
            Key::Named(NamedKey::Escape) => elwt.exit(),
            _ => (),
        }
    }

    fn main_loop(&self, evt_loop: EventLoop<()>) {
        evt_loop.set_control_flow(ControlFlow::Poll);
        evt_loop
            .run(move |evt, elwt| match evt {
                Event::WindowEvent {
                    event: WindowEvent::CloseRequested,
                    ..
                } => elwt.exit(),
                Event::WindowEvent {
                    event: WindowEvent::KeyboardInput { event, .. },
                    ..
                } => self.handle_keys(event.logical_key, elwt),
                _ => (),
            })
            .unwrap();
    }
}

fn main() {
    println!("Rust vktor");

    let inst = core::InstanceState::new()
        .app_name("Rust Vktor")
        .add_layer("VK_LAYER_KHRONOS_validation")
        .into();
    if let Err(err) = inst {
        println!("{:?}", err);
    }

    let evt_loop = EventLoop::new().unwrap();
    let app = App::new(&evt_loop);
    app.main_loop(evt_loop);
}
