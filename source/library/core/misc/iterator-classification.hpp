#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/meta-type/type-inspectors.hpp>                       // type_is_a_

#include <iterator>             // std::iterator_traits etc.

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    using   fsm::type_is_a_;
    using   std::iterator_traits,
            std::input_iterator_tag,
            std::output_iterator_tag,
            std::forward_iterator_tag,
            std::bidirectional_iterator_tag,
            std::random_access_iterator_tag;
    // TODO: C++20 contiguous_iterator_tag
    
    template< class It >
    using   iterator_category_of_ = typename iterator_traits<It>::iterator_category;
    
    template< class It >
    constexpr bool  is_tagged_as_input_         = type_is_a_<input_iterator_tag, iterator_category_of_<It>>;
            
    template< class It >            
    constexpr bool  is_tagged_as_output_        = type_is_a_<output_iterator_tag, iterator_category_of_<It>>;
            
    template< class It >            
    constexpr bool  is_tagged_as_forward_       = type_is_a_<forward_iterator_tag, iterator_category_of_<It>>;
    
    template< class It >    
    constexpr bool  is_tagged_as_bidirectional_ = type_is_a_<bidirectional_iterator_tag, iterator_category_of_<It>>;
    
    template< class It >    
    constexpr bool  is_tagged_as_random_access_ = type_is_a_<random_access_iterator_tag, iterator_category_of_<It>>;

    namespace d = fsm_definitions;
    namespace exports { using
        d::iterator_category_of_,
        d::is_tagged_as_input_,
        d::is_tagged_as_output_,
        d::is_tagged_as_forward_,
        d::is_tagged_as_bidirectional_,
        d::is_tagged_as_random_access_;
    }  // namespace exports
}  // namespace fabulous_support_machinery::_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
