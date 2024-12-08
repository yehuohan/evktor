use crate::core::api::instance::Instance;
use crate::res::Res;
use ash::vk;

#[derive(Default)]
pub struct DeviceState {}

pub struct Device {
    pub(crate) handle: vk::Device,
}
