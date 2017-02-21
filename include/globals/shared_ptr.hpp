#ifndef __BOS_GLOBALS_SHARED_PTR_HPP__
#define __BOS_GLOBALS_SHARED_PTR_HPP__

#ifdef __BOS_USE_STD_C11__
	#include <memory>
	#define bos_ref std::ref
	#define bos_make_shared std::make_shared
	#define bos_unique_ptr std::unique_ptr
	#define bos_shared_ptr std::shared_ptr
	#define bos_weak_ptr std::weak_ptr
	#define bos_enable_shared_from_this std::enable_shared_from_this
	#define bos_dynamic_pointer_cast	std::dynamic_pointer_cast
	#define bos_const_pointer_cast	std::const_pointer_cast
	#define bos_static_pointer_cast	std::static_pointer_cast
#else
	#include <boost/shared_ptr.hpp>
	#include <boost/weak_ptr.hpp>
	#include <boost/scoped_ptr.hpp>
	#include <boost/enable_shared_from_this.hpp>
	#include <boost/noncopyable.hpp>
	#include <boost/smart_ptr/make_shared.hpp>
	#include <boost/ref.hpp>

	#define bos_ref boost::ref
	#define bos_make_shared boost::make_shared
	#define bos_unique_ptr boost::scoped_ptr
	#define bos_shared_ptr boost::shared_ptr
	#define bos_weak_ptr boost::weak_ptr
	#define bos_enable_shared_from_this boost::enable_shared_from_this
	#define bos_dynamic_pointer_cast	boost::dynamic_pointer_cast
	#define bos_const_pointer_cast	boost::const_pointer_cast
	#define bos_static_pointer_cast	boost::static_pointer_cast
#endif

#endif