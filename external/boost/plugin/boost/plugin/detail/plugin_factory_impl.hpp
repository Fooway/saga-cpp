// Copyright Vladimir Prus 2004.
// Copyright Hartmut Kaiser 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#ifndef BOOST_PLUGIN_FACTORY_IMPL_HK_2005_11_07
#define BOOST_PLUGIN_FACTORY_IMPL_HK_2005_11_07

#include <boost/mpl/list.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#include <boost/plugin/config.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (3, PLUGIN_ARGUMENT_LIMIT,                                            \
    "boost/plugin/detail/plugin_factory_impl.hpp"))
#include BOOST_PP_ITERATE()

#endif  // BOOST_PLUGIN_FACTORY_IMPL_HK_2005_11_07

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

///////////////////////////////////////////////////////////////////////////////
namespace detail {

    ///////////////////////////////////////////////////////////////////////////
    template<
        typename BasePlugin, typename Base, 
        BOOST_PP_ENUM_PARAMS(N, typename A)
    >
    struct plugin_factory_item<
        BasePlugin, Base, 
        boost::mpl::list<BOOST_PP_ENUM_PARAMS(N, A)>
    > 
    :   public Base 
    {
        using Base::create;
        BasePlugin* create(std::string const& name, BOOST_PP_ENUM_BINARY_PARAMS(N, A, a))
        {
            std::pair<abstract_factory<BasePlugin> *, dll_handle> r = 
                get_abstract_factory<BasePlugin>(this->m_dll, name);
            return r.first->create(r.second, BOOST_PP_ENUM_PARAMS(N, a));            
        }
    };
    
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename BasePlugin, typename Base,
        BOOST_PP_ENUM_PARAMS(N, typename A)
    >
    struct static_plugin_factory_item<
        BasePlugin, Base, 
        boost::mpl::list<BOOST_PP_ENUM_PARAMS(N, A)>
    > 
    :   public Base 
    {
        using Base::create;
        BasePlugin* create(std::string const& name, BOOST_PP_ENUM_BINARY_PARAMS(N, A, a))
        {
            std::pair<abstract_factory<BasePlugin> *, dll_handle> r = 
                get_abstract_factory_static<BasePlugin>(
                    this->f, &empty_deleter, name);
            return r.first->create(r.second, BOOST_PP_ENUM_PARAMS(N, a));            
        }
    };
    
///////////////////////////////////////////////////////////////////////////////
}   // namespace boost::plugin::detail

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)

