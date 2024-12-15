use crate::core::instance::*;
use crate::res::Res;

pub struct ApiState<'a> {
    pub instance: Option<Instance<'a>>,
}

impl<'a> ApiState<'a> {
    pub fn new() -> Self {
        ApiState { instance: None }
    }

    #[inline]
    pub fn init_instance(&mut self, stt: InstanceState<'a>) -> Res<&Instance<'a>> {
        self.instance = Some(stt.into()?);
        if let Some(instance) = &self.instance {
            return Ok(instance);
        }
        return Err("Failed to initialize instance".into());
    }

    pub fn into(self) -> Res<Api<'a>> {
        Ok(Api {
            instance: self.instance.ok_or("Invalid instance")?,
        })
    }
}

#[allow(dead_code)]
pub struct Api<'a> {
    pub(crate) instance: Instance<'a>,
}
