#include "Component.h"

void dae::Component::AddObserver(IObserver* pObserver)
{
	m_pObservers.emplace_back(pObserver);
}

void dae::Component::RemoveObserver(IObserver* pObserver)
{
	std::erase_if(m_pObservers, [pObserver](const auto& pObserver2)
	{
		return pObserver2 == pObserver;
	});
}

void dae::Component::NotifyObservers(unsigned eventId)
{
	for (auto pObserver : m_pObservers)
	{
		pObserver->ReceiveNotification(eventId, this);
	}
}