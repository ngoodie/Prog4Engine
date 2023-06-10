#pragma once

namespace dae
{
	class Component;
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void ReceiveNotification(unsigned eventId, Component* pComponent) = 0;
	};
}