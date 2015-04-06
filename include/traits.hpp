/** NYSL Version 0.9982
A. This software is "Everyone'sWare". It means:
  Anybody who has this software can use it as if he/she is
  the author.

  A-1. Freeware. No fee is required.
  A-2. You can freely redistribute this software.
  A-3. You can freely modify this software. And the source
      may be used in any software with no limitation.
  A-4. When you release a modified version to public, you
      must publish it with your name.

B. The author is not responsible for any kind of damages or loss
  while using or misusing this software, which is distributed
  "AS IS". No warranty of any kind is expressed or implied.
  You use AT YOUR OWN RISK.

C. Copyrighted to Kazuki KOMATSU(Toyohashi University of Technology).

D. Above three clauses are applied both to source and binary
  form of this software.
*/


#include <type_traits>

/**
D言語のTemplate制約を実現します。

For example:
----------------
// front, popFront, emptyというメンバ関数を持っているかどうか
TUTCCPP_DEF_TYPE_TRAIT(isInputRange, true, (
    p->front(),
    p->popFront(),
    p->empty()
));


// 引数R& rangeには、isInputRangeを満たすような型しか渡せない
template <typename R,
    TUTCCPP_TEMPLATE_CONSTRAINTS(isInputRange<R>())>
void popFrontN(R& range, size_t n)
{
    while(n){
        range.popFront();
        --n;
    }
}
----------------
*/
#define TUTCCPP_TEMPLATE_CONSTRAINTS(b) typename std::enable_if<(b)>::type *& = tutccpp::utils::enabler_ptr

/**
Traitsを定義します。
*/
#define TUTCCPP_DEF_TYPE_TRAIT(name, inh, code) \
template <typename T>                           \
constexpr auto name##_impl(T* p)                \
-> decltype((code, true))                       \
{ return true; }                                \
                                                \
constexpr bool name##_impl(...)                 \
{ return false; }                               \
                                                \
template <typename T>                           \
constexpr bool name()                           \
{                                               \
    return inh && name##_impl(static_cast<      \
    typename std::remove_reference<T>::type*>   \
    (nullptr));                                 \
}


namespace tutccpp { namespace utils {

/**
擬似Concept Liteを構築する際に、enable_ifテクニックで使用する
*/
void* enabler_ptr;

}} // namespace tutccpp::utils
