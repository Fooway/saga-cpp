//  Copyright (c) 2009 STFC
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef SAGA_PACKAGES_SD_CONFIG_HPP
#define SAGA_PACKAGES_SD_CONFIG_HPP

// For symbol import/export macros
#include <saga/saga-defs.hpp>

#if !defined (SAGA_CREATE_PREPROCESSED_FILES)

# ifdef   SAGA_SD_PACKAGE_EXPORTS
#   define SAGA_SD_PACKAGE_EXPORT   SAGA_SYMBOL_EXPORT
#   define SAGA_SD_PACKAGE_EXPORT_REPEAT SAGA_SYMBOL_EXPORT_REPEAT
#   define SAGA_SD_PACKAGE_LOCAL    SAGA_SYMBOL_INTERNAL
# elif !defined(BUILD_SAGA_LITE)
#   define SAGA_SD_PACKAGE_EXPORT   SAGA_SYMBOL_IMPORT
#   define SAGA_SD_PACKAGE_EXPORT_REPEAT /**/
#   define SAGA_SD_PACKAGE_LOCAL    SAGA_SYMBOL_INTERNAL
# else
#   define SAGA_SD_PACKAGE_EXPORT   /* empty */
#   define SAGA_SD_PACKAGE_EXPORT_REPEAT /**/
#   define SAGA_SD_PACKAGE_LOCAL    /* empty */
# endif

#endif // !SAGA_CREATE_PREPROCESSED_FILES

#endif // SAGA_PACKAGES_SD_CONFIG_HPP


