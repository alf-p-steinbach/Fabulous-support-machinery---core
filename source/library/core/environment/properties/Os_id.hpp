#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>           // ref_, array_of_
#include <fsm/core/environment/FSM_OS_IS_xxx.hpp>                       // FSM_OS_IS_xxx
#include <fsm/core/misc/support-for-macros/FSM_AS_STRING_LITERAL.hpp>   // FSM_AS_STRING

#include <string_view>

namespace fsm_definitions{
    namespace fsm = fabulous_support_machinery;
    using   fsm::ref_, fsm::array_of_;
    using   std::string_view;

    #define FSMi_OS_ID_NAMES \
        any, \
        windows, win32, win64, unix, linux, mac_os, ios, ios_in_simulator, ios_on_device, \
        unknown

    struct Os_id{ enum Enum: int { FSMi_OS_ID_NAMES, _ }; };
    constexpr int n_os_ids = Os_id::_;

    struct Os_names
    {
        static constexpr auto s = string_view( FSM_AS_STRING_LITERAL( FSMi_OS_ID_NAMES ) "," );
        array_of_<n_os_ids, string_view>    m_strings;
        
        constexpr Os_names()
        {
            bool            in_space    = true;
            int             id          = 0;
            const char*     p_start     = nullptr;  // Must be initialized in a `constexpr` function.

            for( ref_<const char> ch: s ) {
                if( ch == ',' or ch == ' ' ) {
                    in_space = true;
                    if( p_start ) {
                        const auto length = static_cast<int>( &ch - p_start );
                        m_strings[id] = string_view( p_start, length );
                        ++id;
                        p_start = nullptr;
                    }
                } else if( in_space ) {
                    p_start = &ch;
                    in_space = false;
                }
            }
        }
    };

    inline constexpr Os_names os_names{};

    constexpr auto name_of( const Os_id::Enum id )
        -> string_view
    { return (id < n_os_ids? os_names.m_strings[id] : "<invalid os id value>"); }

    template< Os_id::Enum an_id, class... Sub_types >
    struct Os_{ static constexpr Os_id::Enum id = an_id; };
    
    using Id = Os_id;
    using Os_categories =
        Os_< Id::any,
            Os_< Id::windows,
                Os_< Id::win32 >,
                Os_< Id::win64 >
            >,
            Os_< Id::unix,
                Os_< Id::linux >,
                Os_< Id::mac_os >,
                Os_< Id::ios,
                    Os_< Id::ios_in_simulator >,
                    Os_< Id::ios_on_device >
                >
            >,
            Os_< Id::unknown >
        >;

    using Parent_id_array = array_of_<n_os_ids, Os_id::Enum>;

    template< Os_id::Enum category, class... Sub_types >
    inline void populate(
        ref_<Parent_id_array>           parent_id_array,
        const Os_id::Enum               parent_id,
        Os_<category, Sub_types...>     os
        )
    {
        parent_id_array[os.id] = parent_id;
        (populate( parent_id_array, os.id, Sub_types() ), ...);
    }

    inline auto parent_ids()
        -> ref_<const array_of_<n_os_ids, Os_id::Enum>>
    {
        struct Parent_ids
        {
            Parent_id_array     m_ids = {};
            Parent_ids() { populate( m_ids, Os_id::any, Os_categories() ); }
        };
        
        static const Parent_ids the_parent_ids = {};
        return the_parent_ids.m_ids;
    };

    // constexpr Os_id::Enum os = DETECTED_OS_ID;
    constexpr Os_id::Enum os = Os_id::
    #if defined( FSM_OS_IS_WINDOWS )
        #if defined( FSM_OS_IS_WIN32 )  // Note: is not defined for 64-bit Windows (unlike `_WIN32`).
            win32
        #elif defined( FSM_OS_IS_WIN64 )
            win64
        #else
            windows
        #endif
    #elif defined( FSM_OS_IS_UNIX )
        #if defined( FSM_OS_IS_LINUX )
            linux
        #elif defined( FSM_OS_IS_IOS )
            #if defined( FSM_OS_IS_IOS_IN_SIMULATOR )
                ios_in_simulator
            #elif defined( FSM_OS_IS_IOS_ON_DEVICE )
                ios_on_device
            #else
                ios
            #endif
        #elif defined( FSM_OS_IS_MAC_OS )
            mac_os
        #else
            unix
        #endif
    #else
        unknown
    #endif
    ;
    
    inline auto os_is( const Os_id::Enum a_category, const Os_id::Enum a_specific_os = os )
        -> bool
    {
        Os_id::Enum category = a_specific_os;
        for( ;; ) {
            if( a_category == category ) {
                return true;
            }
            if( category == Os_id::any ) {
                return false;
            }
            category = parent_ids()[category];
        }
        for( ;; ) {}        // Should never get here.
    }
    
    namespace d = fsm_definitions;
    namespace exports{ using
        d::Os_id,
        d::n_os_ids,
        d::name_of,
        d::os,
        d::os_is;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
