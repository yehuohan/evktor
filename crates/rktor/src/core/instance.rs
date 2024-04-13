use super::Res;
use ash::{vk, Entry};
use std::ffi::{c_char, CString};

#[derive(Default)]
pub struct InstanceState<'a> {
    app_name: String,
    app_version: u32,
    engine_name: String,
    engine_version: u32,
    api_version: u32,
    layers: Vec<&'a str>,
    extensions: Vec<&'a str>,
}

impl<'a> InstanceState<'a> {
    pub fn new() -> Self {
        InstanceState { ..Default::default() }
    }

    #[inline]
    pub fn app_name(mut self, name: &str) -> Self {
        self.app_name = String::from(name);
        self
    }

    #[inline]
    pub fn app_version(mut self, version: u32) -> Self {
        self.app_version = version;
        self
    }

    #[inline]
    pub fn engine_name(mut self, name: &str) -> Self {
        self.engine_name = String::from(name);
        self
    }

    #[inline]
    pub fn engine_version(mut self, version: u32) -> Self {
        self.engine_version = version;
        self
    }

    #[inline]
    pub fn api_verion(mut self, version: u32) -> Self {
        self.api_version = version;
        self
    }

    #[inline]
    pub fn add_layer(mut self, layer: &'a str) -> Self {
        self.layers.push(layer);
        self
    }

    #[inline]
    pub fn add_extension(mut self, extension: &'a str) -> Self {
        self.extensions.push(extension);
        self
    }

    #[inline]
    pub fn into(self) -> Res<Instance> {
        Instance::from(self)
    }
}

pub struct Instance {
    pub entry: Entry,
    pub handle: ash::Instance,
}

impl Instance {
    fn from(stt: InstanceState) -> Res<Self> {
        let app_name = CString::new(stt.app_name)?;
        let engine_name = CString::new(stt.engine_name)?;
        let app_info = vk::ApplicationInfo { ..Default::default() }
            .application_name(app_name.as_c_str())
            .application_version(stt.app_version)
            .engine_name(engine_name.as_c_str())
            .engine_version(stt.engine_version)
            .api_version(stt.api_version);
        let mut layers: Vec<*const c_char> = vec![];
        for lyr in stt.layers {
            layers.push((CString::new(lyr)?).as_ptr());
        }
        let mut extensions: Vec<*const c_char> = vec![];
        for ext in stt.extensions {
            extensions.push((CString::new(ext)?).as_ptr());
        }
        let create_info = vk::InstanceCreateInfo { ..Default::default() }
            .application_info(&app_info)
            .enabled_layer_names(layers.as_slice())
            .enabled_extension_names(extensions.as_slice());

        let entry = unsafe { Entry::load()? };
        let handle = unsafe { entry.create_instance(&create_info, None)? };

        Ok(Instance { entry, handle })
    }
}

impl Drop for Instance {
    fn drop(&mut self) {
        unsafe {
            self.handle.destroy_instance(None);
        };
    }
}
