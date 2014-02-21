#include "ObjectAdapter.h"

namespace ObjectAdapter {

	template<typename T>
	T convert<T>(Object object)
	{
		return T(object);
	}
}
