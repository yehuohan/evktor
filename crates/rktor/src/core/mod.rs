mod api;
pub use api::*;

use crate::rkt_impl_err;

rkt_impl_err!(&str, std::ffi::NulError);
rkt_impl_err!(ash::LoadingError, ash::vk::Result);
