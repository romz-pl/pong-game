#pragma once

#include <type_traits>
#include <stdexcept>

template < typename B >
class unique
{
public:
    unique() = default;
    ~unique() = default;

    unique( const unique& ) = delete;
    unique( unique&& ) = delete;

    unique& operator=( const unique& ) = delete;
    unique& operator=( unique&& ) = delete;

    template < typename D = B, typename... Args >
    void init( Args&&... args );

    void destroy();
    B& get();
    bool exists() const;

private:
    void throw_exception( const std::string& function ) const;

private:
    B* m_pointer = nullptr;
};


template< typename B >
template< typename D, typename... Args >
void unique< B >::init( Args&&... args )
{
    if( m_pointer != nullptr )
    {
        throw_exception( __PRETTY_FUNCTION__ );
    }

    static_assert( std::is_same< B, D >::value || std::is_base_of< B, D >::value, "Type D must be derived from B" );
    m_pointer = new D( std::forward< Args >( args )... );
}

template< typename B >
void unique< B >::destroy()
{
    if( m_pointer == nullptr )
    {
        throw_exception( __PRETTY_FUNCTION__ );
    }

    delete m_pointer;
    m_pointer = nullptr;
}

template< typename B >
B& unique< B >::get()
{
    if( m_pointer == nullptr )
    {
        throw_exception( __PRETTY_FUNCTION__ );
    }

    return *m_pointer;
}

template< typename B >
bool unique< B >::exists() const
{
    return m_pointer != nullptr;
}

template< typename B >
void unique< B >::throw_exception( const std::string& function ) const
{
    const std::string txt = "Global variable. Exception thrown in " + function;
    throw std::runtime_error( txt );
}
