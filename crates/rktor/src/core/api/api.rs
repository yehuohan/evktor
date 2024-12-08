use crate::core::api::instance::*;
use crate::core::api::physical_device::*;
use crate::res::Res;

pub struct ApiState {
    pub instance: Option<Instance>,
    pub physical_device: Option<PhysicalDevice>,
}

impl ApiState {
    pub fn new() -> Self {
        ApiState {
            instance: None,
            physical_device: None,
        }
    }

    #[inline]
    pub fn init_instance(&mut self, stt: InstanceState) -> Res<&Instance> {
        self.instance = Some(stt.into()?);
        if let Some(instance) = &self.instance {
            return Ok(instance);
        }
        return Err("Failed to initialize instance".into());
    }

    #[inline]
    pub fn init_physical_device(&mut self, stt: PhysicalDeviceState) -> Res<&PhysicalDevice> {
        if let Some(instance) = &self.instance {
            self.physical_device = Some(stt.into(instance)?);
        }
        if let Some(physical_device) = &self.physical_device {
            return Ok(physical_device);
        }
        return Err("Failed to initialize physical device".into());
    }

    pub fn into(self) -> Res<Api> {
        Ok(Api {
            instance: self.instance.ok_or("Invalid instance")?,
            physical_device: self.physical_device.ok_or("Invalid physical device")?,
        })
    }
}

pub struct Api {
    pub(crate) instance: Instance,
    pub(crate) physical_device: PhysicalDevice,
}
