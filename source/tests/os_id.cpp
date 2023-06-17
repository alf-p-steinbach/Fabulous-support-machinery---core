#define FSMi_TEST_OS_ID
#include <fsm/_simple.hpp>
using   fsm::in_;
using   std::string_view;

auto test( in_<string_view> expr, const bool result, const bool expected )
    -> bool
{
    const bool success = (result == expected);
    display( (success? "ok" : "FAILED"), ": (", expr, ") = ", result, "\n" );
    return success;
}

#define TEST( n, expr, expected )  (test( #expr, expr, expected )? 0 : throw n)

auto main() -> int
{
    display( "OS = ", fsm::name_of( fsm::os ), ".\n" );
    
    const auto assumed_os = fsm::Os_id::ios;
    display( "\n" );
    display( "Using assumed OS ", fsm::name_of( assumed_os ), ".\n" );
    try {

        TEST( 1, fsm::os_is( fsm::Os_id::ios_in_simulator, assumed_os ), false );
        TEST( 2, fsm::os_is( fsm::Os_id::ios, assumed_os ), true );
        TEST( 3, fsm::os_is( fsm::Os_id::unix, assumed_os ), true );
        TEST( 4, fsm::os_is( fsm::Os_id::any, assumed_os ), true );
        TEST( 5, fsm::os_is( fsm::Os_id::windows, assumed_os ), false );

    } catch( const int id_fail ) {
        display_err( "!Test #", id_fail, " failed.\n" );
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
