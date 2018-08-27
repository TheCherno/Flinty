#pragma once

#include "fl/Common.h"
#include "fl/math/math.h"

#include "fl/events/KeyEvent.h"
#include "fl/events/MouseEvent.h"

namespace fl {

	class FL_API MayaCamera
	{
	public:
		MayaCamera(const math::mat4& projection);
		~MayaCamera() {}

		void Focus();
		void Update();

		void OnMouseButtonPressed(const MouseButtonEvent& event);
		void OnMouseMoved(const MouseMovedEvent& event);
		void OnKeyPressed(const KeyPressedEvent& event);

		inline const math::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const math::vec3& position) { m_Position = position; }

		inline const math::vec3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const math::vec3& rotation) { m_Rotation = rotation; }

		inline const math::mat4& GetProjectionMatrix() const { return m_Projection; }
		inline void SetProjectionMatrix(const math::mat4& projectionMatrix) { m_Projection = projectionMatrix; }

		inline void Translate(const math::vec3& translation) { m_Position += translation; }
		inline void Rotate(const math::vec3& rotation) { m_Rotation += rotation; }

		inline void Translate(float x, float y, float z) { m_Position += math::vec3(x, y, z); }
		inline void Rotate(float x, float y, float z) { m_Rotation += math::vec3(x, y, z); }

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline const math::vec3& GetFocalPoint() const { return m_FocalPoint; }
		inline const math::mat4& GetViewMatrix() { return m_View; }
	private:
		void MousePan(const math::vec2& delta);
		void MouseRotate(const math::vec2& delta);
		void MouseZoom(float delta);

		math::vec3 GetUpDirection();
		math::vec3 GetRightDirection();
		math::vec3 GetForwardDirection();

		math::vec3 CalculatePosition();
		math::Quaternion GetOrientation();
	private:
		math::mat4 m_Projection, m_View;
		math::vec3 m_Position, m_Rotation, m_FocalPoint;

		bool m_Panning, m_Rotating;
		math::vec2 m_InitialMousePosition;
		math::vec3 m_InitialFocalPoint, m_InitialRotation;

		float m_Distance;
		float m_PanSpeed, m_RotationSpeed, m_ZoomSpeed;

		float m_Pitch, m_Yaw;
	};
}