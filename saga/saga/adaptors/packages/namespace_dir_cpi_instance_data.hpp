//  Copyright (c) 2005-2009 Hartmut Kaiser
//  Copyright (c) 2005-2007 Andre Merzky (andre@merzky.net)
//  Copyright (c) 2005 Michel Zandstra [michelzandstra@gmail.com]
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef SAGA_SAGA_ADAPTORS_NAMESPACE_DIR_CPI_INSTANCE_DATA_HPP
#define SAGA_SAGA_ADAPTORS_NAMESPACE_DIR_CPI_INSTANCE_DATA_HPP

#include <saga/saga/packages/namespace/namespace_dir.hpp>
#include <saga/saga/adaptors/config.hpp>
#include <saga/saga/types.hpp>
#include <saga/saga/adaptors/instance_data_base.hpp>
#include <saga/saga/adaptors/packages/namespace_entry_cpi_instance_data.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace saga { namespace adaptors { namespace v1_0 
{
  ///////////////////////////////////////////////////////////////////////////
  //  Instance data held by the SAGA engine/package
  //  This should be used as a base class when adding additional instance 
  //  data for an adaptor.
  struct namespace_dir_cpi_instance_data 
      : public namespace_entry_cpi_instance_data
  {
    namespace_dir_cpi_instance_data (saga::url location, int mode)
        : namespace_entry_cpi_instance_data(location, mode) 
    {
    }
  };
  
} } } // namespace saga::adaptors::v1_0
///////////////////////////////////////////////////////////////////////////////

#endif // SAGA_SAGA_ADAPTORS_NAMESPACE_CPI_DIR_INSTANCE_DATA_HPP

