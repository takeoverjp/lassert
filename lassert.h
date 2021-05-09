/*
 * Copyright (C) 2021 takeoverjp@gmail.com
 * All rights reserved.
 */

#ifndef LASSERT_H_
#define LASSERT_H_

#include <iostream>
#include <string>

namespace lassert {

template <typename ScopedEnumType,
          typename std::enable_if<std::is_enum<ScopedEnumType>::value,
                                  std::nullptr_t>::type = nullptr>
static inline std::ostream &operator<<(std::ostream &ostrm,
                                       ScopedEnumType val) {
  ostrm << static_cast<typename std::underlying_type<ScopedEnumType>::type>(
      val);
  return ostrm;
}

template <class>
struct is_container : std::false_type {};

template <class T, class ALLOCATOR>
struct is_container<std::set<T, ALLOCATOR>> : std::true_type {};

template <class T, class ALLOCATOR>
struct is_container<std::vector<T, ALLOCATOR>> : std::true_type {};

template <class T, class ALLOCATOR>
struct is_container<std::unordered_set<T, ALLOCATOR>> : std::true_type {};

template <typename ContainerType,
          typename std::enable_if<is_container<ContainerType>::value,
                                  std::nullptr_t>::type = nullptr>
static inline std::ostream &operator<<(std::ostream &ostrm, ContainerType val) {
  if (val.empty()) {
    ostrm << "[]";
    return ostrm;
  }
  ostrm << "[";
  for (const auto &mem : val) {
    ostrm << mem << ", ";
  }
  ostrm << "\b\b]";
  return ostrm;
}

#if __cplusplus >= 201402L
static inline void ASSERT_EQ_IMPL(const std::string &file, const int lineno,
                                  const std::string &func,
                                  const std::string &exp_symbol,
                                  const auto &exp,
                                  const std::string &act_symbol,
                                  const auto &act) {
#else
template <class T1, class T2>
static inline void ASSERT_EQ_IMPL(const std::string &file, const int lineno,
                                  const std::string &func,
                                  const std::string &exp_symbol, const T1 &exp,
                                  const std::string &act_symbol,
                                  const T2 &act) {
#endif
  if (exp == act) {
    return;
  }
  std::cerr << file << ": " << lineno << ": " << func << ": error: check "
            << exp_symbol << " == " << act_symbol << " has failed [" << exp
            << " != " << act << "]" << std::endl;
#if !defined(TEST_LASSERT)
  std::terminate();
#endif
}

#define ASSERT_EQ(exp, act)                                                \
  do {                                                                     \
    lassert::ASSERT_EQ_IMPL(__FILE__, __LINE__, __PRETTY_FUNCTION__, #exp, \
                            exp, #act, act);                               \
  } while (0)

}  // namespace lassert
#endif  // LASSERT_H_
