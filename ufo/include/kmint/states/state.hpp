#ifndef KMINT_UFO_STATE_HPP
#define KMINT_UFO_STATE_HPP

#include <string>

namespace kmint::states
{
	template <class entity_type>
	class state
	{
	public:
	
		virtual ~state() = default;
		virtual void on_enter(entity_type&) = 0;
		virtual void execute(entity_type&) = 0;
		virtual void on_exit(entity_type&) = 0;
		virtual std::string name() = 0;
	};
	
}

#endif /* KMINT_UFO_STATE_HPP */