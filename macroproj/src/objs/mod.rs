//use std::ops::IndexMut;
//use std::collections::HashMap;
//use std::hash::{Hash, BuildHasher};
//use std::borrow::Borrow;

pub mod base;
pub mod load;

//impl<K, V, S, Q: ?Sized> IndexMut<Q> for HashMap<K, V, S>
//    where K: Eq + Hash + Borrow<Q>,
//          Q: Eq + Hash,
//          S: BuildHasher,
//{
//    #[inline]
//    fn index_mut<'a>(&'a mut self, index: &Q) -> &'a mut V {
//        self.get_mut(index).expect("no entry found for key")
//    }
//} //i literally hate rust so much, can't even let me re-implement when their stupid lazy a*ses can't
