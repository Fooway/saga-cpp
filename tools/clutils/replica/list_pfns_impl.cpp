//  Copyright (c) 2008 Ole Weidner
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <saga/saga.hpp>
#include "saga-replica.hpp"

///////////////////////////////////////////////////////////////////////////////
#if defined(SAGA_HAVE_PACKAGE_REPLICA) && defined(SAGA_HAVE_PACKAGE_NAMESPACE)

void replica_list_pfns (saga_tools::common & c,
                        std::string          lfn)
{
  // instantiate logical file 
  saga::replica::logical_file lf (c.session (), saga::url (lfn));

  // read replica entries
  std::vector <saga::url> locations (lf.list_locations ());
  std::vector <saga::url>::const_iterator it;

  for ( it = locations.begin (); it != locations.end (); ++it )
  {
    std::cout << "  " << (*it) << std::endl;
  }
}

#endif
