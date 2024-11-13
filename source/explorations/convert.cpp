struct S
{
    template< class R >
    operator R() const { return {}; }
};

void foo( unsigned ) {}

auto main() -> int
{
    foo( S() );         // OK
    S() + 0.5;          //! Fail.
}
