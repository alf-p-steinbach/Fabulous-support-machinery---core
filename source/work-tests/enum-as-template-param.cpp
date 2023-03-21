template< class E >
struct Foo_ {};

#if 0
struct Input_stream_id
{
    const int   value;

    struct Names
    {
        enum Enum { in = 0 };
    };

    Input_stream_id( const Names::Enum a_value ): value( a_value ) {}

    operator int() const {
        return value;
    }
};
#endif

template< class Wrapped_basic_enum, class... Other_distinct_subsets >
struct Extensible_enum_
{
    const int   value;

    struct Names: Wrapped_basic_enum, Other_distinct_subsets::Names... {};

    template< class Other >
    Extensible_enum_( const Other id ): value( id ) {}

    operator int() const {
        return value;
    }
};

struct Input_stream_id_names {
    enum Enum { in = 0 };
};
using Input_stream_id = Extensible_enum_<Input_stream_id_names>;

struct Output_stream_id_names {
    enum Enum { out = 1, err = 2 };
};
using Output_stream_id = Extensible_enum_<Output_stream_id_names>;

struct Stream_id_names {
    enum Enum {};
};
using Stream_id = Extensible_enum_<Stream_id_names, Input_stream_id, Output_stream_id>;

auto main() -> int
{
    const auto id = Stream_id( Input_stream_id::Names::in );
    (void) id;
}
