#pragma once

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"

class Object
{
protected:
	glm::vec3 pos;
	glm::quat rot;

public:
	virtual ~Object() = default;
	explicit Object(glm::vec3 pos, glm::quat rot = {1, 0, 0, 0});

	glm::vec3 getPos() const { return pos; }
	glm::quat getRot() const { return rot; }
	void setPos(glm::vec3 pos);
	void setRot(glm::quat rot);

	virtual void translate(const glm::vec3& v);
	virtual void rotate(const glm::vec3& degrees);

	glm::vec3 forward() const;
	glm::vec3 backward() const;
	glm::vec3 up() const;
	glm::vec3 down() const;
	glm::vec3 left() const;
	glm::vec3 right() const;

	glm::vec3 localToGlobalPos(const glm::vec3& localPos) const;
	glm::vec3 globalToLocalPos(const glm::vec3& globalPos) const;
};
