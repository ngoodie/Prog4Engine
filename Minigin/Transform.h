#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetCachedPosition() const { return m_CachedPosition; }
		void SetPosition(float x, float y, float z);
		void SetCachedPosition(const glm::vec3& position) { m_CachedPosition = position; }
		bool IsDirty() const { return m_IsDirty; }
		void SetDirty(bool isDirty) { m_IsDirty = isDirty; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_CachedPosition;
		bool m_IsDirty = false;
	};
}