#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").
#include <fsm/core/+std-cpp-language.hpp>

#include <fsm/core/constructs/declarations/type_builders.hpp>       // in_, ref_
#include <fsm/stdlib-alts/filesystem/u8-support.hpp>                // sfs_path_from, u8_from

#include <utility>

namespace fsm_definitions {
    namespace fsm = fabulous_support_machinery;
    namespace sfs = std::filesystem;
    
    using   fsm::in_, fsm::ref_,
            fsm::sfs_path_from, fsm::u8_from;
    using   std::move;                                  // <utility>

    class Path
    {
        sfs::path        m_path;

    public:
        class Computer;
        class Drive;
        class Steps;

        Path() {}
        Path( sfs::path path ): m_path( move( path ) ) {}

        template< class String >
        Path( in_<String> path_spec ): m_path( sfs_path_from( path_spec ) ) {}

        auto u8() const -> string { return u8_from( m_path ); }

        auto sfs_path() const       -> ref_<const sfs::path>    { return m_path; }
        auto operator~ () const     -> ref_<const sfs::path>    { return sfs_path(); }
        operator const sfs::path& () const                      { return sfs_path(); }
    };

    namespace d = fsm_definitions;
    namespace exports{ using
        d::Path;
    }  // namespace exports
}  // namespace fsm_definitions

namespace fabulous_support_machinery    { using namespace fsm_definitions::exports; }
