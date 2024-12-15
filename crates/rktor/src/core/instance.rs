use crate::res::Res;
use ash::{vk, Entry};
use std::ffi::{c_char, CString};

#[derive(Default)]
pub struct InstanceState<'a> {
    pub(crate) allocator: Option<&'a vk::AllocationCallbacks<'a>>,
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
        InstanceState {
            allocator: None,
            app_name: String::from("rktor"),
            app_version: vk::make_api_version(0, 1, 0, 0),
            engine_name: String::from("rktor"),
            engine_version: vk::make_api_version(0, 1, 0, 0),
            api_version: vk::make_api_version(0, 1, 0, 0),
            layers: vec![],
            extensions: vec![],
        }
    }

    #[inline]
    pub fn allocation_callbacks(mut self, allocator: &'a vk::AllocationCallbacks<'a>) -> Self {
        self.allocator = Some(allocator);
        self
    }

    #[inline]
    pub fn app_name(mut self, name: &str) -> Self {
        self.app_name = String::from(name);
        self
    }

    #[inline]
    pub fn app_version(mut self, major: u32, minor: u32, patch: u32) -> Self {
        self.app_version = vk::make_api_version(0, major, minor, patch);
        self
    }

    #[inline]
    pub fn engine_name(mut self, name: &str) -> Self {
        self.engine_name = String::from(name);
        self
    }

    #[inline]
    pub fn engine_version(mut self, major: u32, minor: u32, patch: u32) -> Self {
        self.engine_version = vk::make_api_version(0, major, minor, patch);
        self
    }

    #[inline]
    pub fn api_version(mut self, major: u32, minor: u32, patch: u32) -> Self {
        self.api_version = vk::make_api_version(0, major, minor, patch);
        self
    }

    #[inline]
    pub fn add_layer(mut self, layer: &'a str) -> Self {
        self.layers.push(layer);
        self
    }

    #[inline]
    pub fn enable_layer_validation(self) -> Self {
        self.add_layer("VK_LAYER_KHRONOS_validation")
    }

    #[inline]
    pub fn add_extension(mut self, extension: &'a str) -> Self {
        self.extensions.push(extension);
        self
    }

    #[inline]
    pub fn into(self) -> Res<Instance<'a>> {
        Instance::from(self)
    }
}

#[allow(dead_code)]
pub struct Instance<'a> {
    pub(crate) allocator: Option<&'a vk::AllocationCallbacks<'a>>,
    pub(crate) entry: Entry,
    pub(crate) handle: ash::Instance,
}

impl<'a> Instance<'a> {
    fn from(mut stt: InstanceState<'a>) -> Res<Self> {
        let entry = unsafe { Entry::load()? };

        stt.layers.sort_unstable();
        stt.layers.dedup();
        stt.extensions.sort_unstable();
        stt.extensions.dedup();

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

        let handle = unsafe { entry.create_instance(&create_info, stt.allocator)? };

        Ok(Instance {
            allocator: stt.allocator,
            entry,
            handle,
        })
    }
}

impl<'a> Into<Option<&'a vk::AllocationCallbacks<'a>>> for Instance<'a> {
    fn into(self) -> Option<&'a vk::AllocationCallbacks<'a>> {
        self.allocator
    }
}

impl<'a> Drop for Instance<'a> {
    fn drop(&mut self) {
        unsafe {
            self.handle.destroy_instance(self.allocator);
        };
    }
}
