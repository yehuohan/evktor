use crate::core::api::instance::Instance;
use crate::res::Res;
use ash::vk;

#[derive(Default)]
pub struct PhysicalDeviceState {}

impl PhysicalDeviceState {
    pub fn into(self, instance: &Instance) -> Res<PhysicalDevice> {
        PhysicalDevice::from(instance, self)
    }
}

pub struct PhysicalDevice {
    pub(crate) handle: vk::PhysicalDevice,
}

impl PhysicalDevice {
    pub fn from(instance: &Instance, stt: PhysicalDeviceState) -> Res<Self> {
        let phy_devs = unsafe { instance.handle.enumerate_physical_devices()? };
        let handle = phy_devs[0];

        Ok(PhysicalDevice { handle })
    }
}
