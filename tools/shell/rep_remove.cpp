//  Copyright (c) 2005-2008 Andre Merzky
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "saga-shell.hpp"

// remove a given location from a logical file
int shell::c_rep_remove (std::vector <std::string> & args,
                         props & p)
{
#if !defined(SAGA_HAVE_PACKAGE_REPLICA) || !defined(SAGA_HAVE_PACKAGE_NAMESPACE)
    carp("saga has been compiled without the replica package, unable to use this command");
    return FAILURE;
#else
  if ( args.size () != 2 )
  {
    carp ("format: rep_remove <logical_file> <url>", p);
    return FAILURE;
  }

  std::string src = args[0];
  std::string url = args[1];

  // sanity checks
  if ( ! cwd_.exists (src) )
  {
    carp ("No such logical file: " + src, p);
    return FAILURE;
  }

  if ( cwd_.is_dir (src) )
  {
    carp ("Cannot remove replica from directory: " + src, p);
    return FAILURE;
  }

  // open the current directory as logical dir
  saga::replica::logical_directory dir (cwd_.get_url ());

  // open the logical file
  saga::replica::logical_file lf = 
         dir.open (src, saga::replica::Write);

  // remove the replica location
  lf.remove_location (saga::url (url));

  // logical file and dir close when going out of scope
  return SUCCESS;
#endif
}

