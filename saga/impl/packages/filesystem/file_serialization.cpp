//  Copyright (c) 2005-2009 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

#include <saga/saga/error.hpp>
#include <saga/saga/adaptors/instance_data.hpp>
#include <saga/saga/adaptors/packages/file_cpi_instance_data.hpp>
#include <saga/saga/adaptors/packages/directory_cpi_instance_data.hpp>

#include <saga/saga/packages/filesystem/version.hpp>
#include <saga/impl/packages/filesystem/file_serialization.hpp>

#include <saga/impl/packages/filesystem/file.hpp>
#include <saga/impl/packages/filesystem/directory.hpp>

///////////////////////////////////////////////////////////////////////////////
// Register the serialization factory type
SAGA_PACKAGE_REGISTER(saga::impl::file_serialization);

///////////////////////////////////////////////////////////////////////////////
namespace saga { namespace impl
{

    file_serialization::~file_serialization()
    {
    }

    std::string 
    file_serialization::serialize(TR1::shared_ptr<saga::impl::object> obj)
    {
        // get the type of the object (has been serialized already)
        saga::object::type type = obj->get_type();
        if (saga::object::File != type && saga::object::Directory != type) 
        {
            SAGA_THROW_VERBATIM(obj.get(), "file_serialization::serialize: " 
                "Unknown object type", saga::BadParameter);
        }

        SAGA_OSSTREAM strm;
        {
            using namespace boost::serialization;
            using namespace boost::archive;

            // the object actually is a impl::file or impl::directory, so the
            // following cast should succeed
            saga::impl::proxy *proxy = dynamic_cast<saga::impl::proxy *>(obj.get());
            if (NULL == proxy)
            {
                SAGA_THROW_VERBATIM(obj.get(), "file_serialization::serialize: " 
                    "Unknown object type", saga::BadParameter);
            }

            // save package version
            text_oarchive oa(strm);
            unsigned int version = SAGA_VERSION_PACKAGE_FILESYSTEM_FULL;
            oa << make_nvp("version", version);

            if (saga::object::File == type) {
            // serialize the file_cpi_instance data
                typedef saga::adaptors::v1_0::file_cpi_instance_data 
                    instance_data;

            saga::adaptors::instance_data<instance_data> data(proxy);
            std::string url (data->location_.get_url());

                oa << make_nvp("location", url);
                oa << make_nvp("mode", data->mode_);
                oa << make_nvp("pointer", data->pointer_);
            }
            else {
            // saga::object::Directory == type: serialize the 
            // directoy_cpi_instance data
                typedef saga::adaptors::v1_0::directory_cpi_instance_data 
                    instance_data;

            saga::adaptors::instance_data<instance_data> data(proxy);
            std::string url (data->location_.get_url());
            
                oa << make_nvp("location", url);
                oa << make_nvp("mode", data->mode_);
            }
        }
        return SAGA_OSSTREAM_GETSTRING(strm);
    }

    TR1::shared_ptr<saga::impl::object> 
    file_serialization::deserialize(saga::session s, saga::object::type type,
        std::string const& data)
    {
        if (saga::object::File != type && saga::object::Directory != type) 
        {
            SAGA_THROW_VERBATIM(s, "file_serialization::deserialize: " 
                "Unknown object type", saga::BadParameter);
        }

        using namespace boost::serialization;
        using namespace boost::archive;

        SAGA_ISSTREAM strm(data);
        text_iarchive ia(strm);

        // save package version
        unsigned int version = 0;
        ia >> make_nvp("version", version);
        if (!SAGA_VERSION_PACKAGE_FILESYSTEM_ISCOMPATIBLE_EX(version)) 
        {
            SAGA_THROW_VERBATIM(s, "file_serialization::deserialize: "
                "Deserialization failed: incompatible version of SAGA file "
                "package module.", saga::NoSuccess);
        }

        TR1::shared_ptr<saga::impl::object> impl;
        if (saga::object::File == type) {
        // deserialize the file_cpi_instance data
        std::string location;
        int mode = 0;
        saga::off_t pointer = 0;

            ia >> make_nvp("location", location);
            ia >> make_nvp("mode", mode);
            ia >> make_nvp("pointer", pointer);
            impl.reset(new saga::impl::file(s, location, mode, pointer));
        }
        else {
        // saga::object::Directory == type: deserialize the 
        // directoy_cpi_instance data
        std::string location;
        int mode = 0;

            ia >> make_nvp("location", location);
            ia >> make_nvp("mode", mode);
            impl.reset(new saga::impl::directory(s, location, mode));
        }

        return impl;
    }

///////////////////////////////////////////////////////////////////////////////
}}    // namespace saga::impl
