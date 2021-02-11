/*
 * Copyright (C) 2021 takeoverjp@gmail.com
 * All rights reserved.
 */

#ifndef LASSERT_H_
#define LASSERT_H_

#include <iostream>
#include <string>

template <typename tEnum,
          typename std::enable_if<std::is_enum<tEnum>::value,
                                  std::nullptr_t>::type = nullptr>
static inline std::ostream &operator<<(std::ostream &iOStream, tEnum iEnum) {
  typedef typename std::underlying_type<tEnum>::type Type;
  iOStream << static_cast<Type>(iEnum);
  return iOStream;
}

#if __cplusplus >= 201402L
static inline void
ASSERT_EQ_IMPL(const std::string &func, const std::string &file,
               const int lineno, const std::string &exp_symbol, const auto &exp,
               const std::string &act_symbol, const auto &act) {
#else
template <class T1, class T2>
static inline void
ASSERT_EQ_IMPL(const std::string &func, const std::string &file,
               const int lineno, const std::string &exp_symbol, const T1 &exp,
               const std::string &act_symbol, const T2 &act) {
#endif
  if (exp == act) {
    return;
  }
  std::cerr << file << ": " << lineno << ": " << func << ": error: check "
            << exp_symbol << " == " << act_symbol << " has failed [" << exp
            << " != " << act << "]" << std::endl;
#if defined(TEST_LASSERT)
  std::terminate();
#endif
}

#define ASSERT_EQ(exp, act)                                                    \
  do {                                                                         \
    ASSERT_EQ_IMPL(__func__, __FILE__, __LINE__, #exp, exp, #act, act);        \
  } while (0)

#endif // LASSERT_H_
