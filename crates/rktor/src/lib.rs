//! rktor is the rust vktor library

pub mod core;

#[macro_export]
macro_rules! rkt_fmt {
    () => {
        format!("[rkt]")
    };
    ($($arg:tt)*) => {
        format!("[rkt] {}", format!($($arg)*))
    };
}

#[macro_export]
macro_rules! rkt_out {
    ($($arg:tt)*) => {{
        print!("{}\n", $crate::rkt_fmt!($($arg)*))
    }};
}

#[macro_export]
macro_rules! rkt_impl_err {
    ($t:ty) => {
        impl From<$t> for crate::res::ResErr {
            fn from(error: $t) -> Self {
                crate::res::ResErr { msg: error.to_string() }
            }
        }
    };
    ($t:ty, $($r:ty),+) => {
        rkt_impl_err!($t);
        rkt_impl_err!($($r),+);
    };
}

pub mod res {
    pub type Res<T> = Result<T, ResErr>;

    pub struct ResErr {
        pub msg: String,
    }

    impl std::fmt::Debug for ResErr {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            write!(f, "{}", rkt_fmt!("Res: {}", self.msg))
        }
    }
}
