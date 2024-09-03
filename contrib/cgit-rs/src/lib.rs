use std::ffi::{c_char, c_int, c_void, CStr, CString};

use cgit_sys::*;

pub struct ConfigSet(*mut config_set);
impl ConfigSet {
    pub fn new() -> Self {
        unsafe {
            let ptr = libgit_configset_alloc();
            libgit_configset_init(ptr);
            ConfigSet(ptr)
        }
    }

    // NEEDSWORK: maybe replace &str with &Path
    pub fn add_files(&mut self, files: &[&str]) {
        for file in files {
            let rs = CString::new(*file).expect("Couldn't convert to CString");
            unsafe {
                libgit_configset_add_file(self.0, rs.as_ptr());
            }
        }
    }

    pub fn get_int(&mut self, key: &str) -> Option<c_int> {
        let key = CString::new(key).expect("Couldn't convert to CString");
        let mut val: c_int = 0;
        unsafe {
            if libgit_configset_get_int(self.0, key.as_ptr(), &mut val as *mut c_int) != 0 {
                return None;
            }
        }

        Some(val)
    }

    pub fn get_str(&mut self, key: &str) -> Option<CString> {
        let key = CString::new(key).expect("Couldn't convert to CString");
        let mut val: *mut c_char = std::ptr::null_mut();
        unsafe {
            if libgit_configset_get_string(self.0, key.as_ptr(), &mut val as *mut *mut c_char) != 0
            {
                return None;
            }
            let borrowed_str = CStr::from_ptr(val);
            let owned_str = CString::from_vec_with_nul(borrowed_str.to_bytes_with_nul().to_vec());
            free(val as *mut c_void); // Free the xstrdup()ed pointer from the C side
            Some(owned_str.unwrap())
        }
    }
}

impl Default for ConfigSet {
    fn default() -> Self {
        Self::new()
    }
}

impl Drop for ConfigSet {
    fn drop(&mut self) {
        unsafe {
            libgit_configset_clear_and_free(self.0);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn load_configs_via_configset() {
        // NEEDSWORK: we need to supply a testdata config
        let mut cs = ConfigSet::new();
        let mut path = std::env::home_dir().expect("cannot get home directory path");
        path.push(".gitconfig");
        let path: String = path.into_os_string().into_string().unwrap();
        cs.add_files(&["/etc/gitconfig", ".gitconfig", &path]);
        assert_eq!(cs.get_int("trace2.eventNesting"), Some(5));
        assert_eq!(cs.get_str("no_such_config_item"), None);
    }
}
