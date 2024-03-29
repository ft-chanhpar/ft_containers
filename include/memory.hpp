/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:28:40 by chanhpar          #+#    #+#             */
/*   Updated: 2022/12/16 19:08:31 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_MEMORY_HPP
#define FT_CONTAINERS_MEMORY_HPP

#include <stdexcept>
#include "iterator.hpp"

namespace ft {

template <typename T>
T*
addressof(T& val) throw() {
  return (reinterpret_cast<T*>(
      &const_cast<char&>(reinterpret_cast<const volatile char&>(val))));
}

template <typename T, typename Allocator>
void
destroy_at(T* p, Allocator& alloc) {
  alloc.destroy(p);
}

template <typename ForwardIter, typename Allocator>
void
destroy(ForwardIter first, ForwardIter last, Allocator& alloc) {
  for (; first != last; ++first)
    alloc.destroy(ft::addressof(*first));
}

template <typename ForwardIter, typename Size, typename Allocator>
void
destroy_n(ForwardIter first, Size count, Allocator& alloc) {
  for (; count > 0; --count, (void)++first)
    alloc.destroy(ft::addressof(*first));
}

template <typename InputIter, typename ForwardIter, typename Allocator>
ForwardIter
uninitialized_copy(InputIter first,
                   InputIter last,
                   ForwardIter d_first,
                   Allocator& alloc) {
  ForwardIter it(d_first);
  try {
    for (; first != last; ++first, (void)++it)
      alloc.construct(ft::addressof(*it), *first);
  } catch (...) {
    for (; d_first != it; ++d_first)
      alloc.destroy(ft::addressof(*d_first));
    throw;
  }
  return (it);
}

template <typename InputIter,
          typename Size,
          typename ForwardIter,
          typename Allocator>
ForwardIter
uninitialized_copy_n(InputIter first,
                     Size count,
                     ForwardIter d_first,
                     Allocator& alloc) {
  ForwardIter it(d_first);
  try {
    for (; count > 0; ++first, (void)--count, (void)++it)
      alloc.construct(ft::addressof(*it), *first);
  } catch (...) {
    for (; d_first != it; ++d_first)
      alloc.destroy(ft::addressof(*d_first));
    throw;
  }
  return (it);
}

template <typename ForwardIter, typename T, typename Allocator>
void
uninitialized_fill(ForwardIter first,
                   ForwardIter last,
                   const T& val,
                   Allocator& alloc) {
  ForwardIter it(first);
  try {
    for (; it != last; ++it)
      alloc.construct(ft::addressof(*it), val);
  } catch (...) {
    for (; first != it; ++first)
      alloc.destroy(ft::addressof(*first));
    throw;
  }
}

template <typename ForwardIter, typename Size, typename T, typename Allocator>
ForwardIter
uninitialized_fill_n(ForwardIter first,
                     Size count,
                     const T& val,
                     Allocator& alloc) {
  ForwardIter it(first);
  try {
    for (; count > 0; --count, (void)++it)
      alloc.construct(ft::addressof(*it), val);
  } catch (...) {
    for (; first != it; ++first)
      alloc.destroy(ft::addressof(*first));
    throw;
  }
  return (it);
}

}  // namespace ft

#endif  // FT_CONTAINERS_MEMORY_HPP
