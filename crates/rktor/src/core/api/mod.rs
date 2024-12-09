mod api;
mod device;
mod instance;
mod physical_device;
mod queue;
mod surface;
pub use api::*;
pub use device::*;
pub use instance::*;
pub use physical_device::*;
// pub use queue::*;
// pub use surface::*;

// pub trait CoreHandle<T: Into<T>> {}

// impl From<CoreHandle<T>> for T {
//     fn from(value: CoreHandle<T>) -> Self {
//     }
// }
