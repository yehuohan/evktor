mod instance;
pub use instance::*;

#[macro_export]
macro_rules! impl_err {
    ($t:ty) => {
        impl From<$t> for Error {
            fn from(error: $t) -> Self {
                Error::from(error.to_string())
            }
        }
    };
}

pub type Res<T> = Result<T, Error>;

#[derive(Debug)]
pub struct Error {
    pub msg: String,
}

impl Error {
    pub fn from(msg: String) -> Self {
        Error { msg }
    }
}

impl_err!(std::ffi::NulError);
impl_err!(ash::LoadingError);
impl_err!(ash::vk::Result);
