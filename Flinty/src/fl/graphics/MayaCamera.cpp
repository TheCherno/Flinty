#include "MayaCamera.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "fl/Input.h"

#include <GLFW/glfw3.h>

namespace fl {

	using namespace math;

	MayaCamera::MayaCamera(const mat4& projectionMatrix)
		: m_Projection(projectionMatrix), m_View(math::mat4::Identity())
	{
		// Sensible defaults
		m_PanSpeed = 0.0015f;
		m_RotationSpeed = 0.002f;
		m_ZoomSpeed = 0.2f;

		m_Position = vec3(0.0f, 25.0f, -25.0f);
		m_Rotation = vec3(90.0f, 0.0f, 0.0f);

		m_FocalPoint = vec3::Zero();
		m_Distance = m_Position.Distance(m_FocalPoint);

		m_Yaw = 3.0f * (float)M_PI / 4.0f;
		m_Pitch = (float)M_PI / 4.0f;
	}

	void MayaCamera::Focus()
	{
		// Input::GetInputManager()->SetMouseCursor(1);
	}

	void MayaCamera::Update()
	{
		if (Input::IsKeyPressed(GLFW_KEY_LEFT_ALT))
		{
			const vec2& mouse = Input::GetMousePosition();
			vec2 delta = mouse - m_InitialMousePosition;
			m_InitialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
				MouseZoom(delta.y);
		}

		// MouseZoom(window->GetMouseScrollPosition().y);

		m_Position = CalculatePosition();

		Quaternion orientation = GetOrientation();
		m_Rotation = orientation.ToEulerAngles() * (180.0f / (float)M_PI);

		m_View = mat4::Translate(vec3(0, 0, 1)) * mat4::Rotate(orientation.Conjugate()) * mat4::Translate(-m_Position);
	}

	void MayaCamera::MousePan(const vec2& delta)
	{
		m_FocalPoint += -GetRightDirection() * delta.x * m_PanSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * m_PanSpeed * m_Distance;
	}

	void MayaCamera::MouseRotate(const vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
	}

	void MayaCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * m_ZoomSpeed;
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	vec3 MayaCamera::GetUpDirection()
	{
		return Quaternion::Rotate(GetOrientation(), vec3::YAxis());
	}

	vec3 MayaCamera::GetRightDirection()
	{
		return Quaternion::Rotate(GetOrientation(), vec3::XAxis());
	}

	vec3 MayaCamera::GetForwardDirection()
	{
		return Quaternion::Rotate(GetOrientation(), -vec3::ZAxis());
	}

	vec3 MayaCamera::CalculatePosition()
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	Quaternion MayaCamera::GetOrientation()
	{
		return Quaternion::RotationY(-m_Yaw) * Quaternion::RotationX(-m_Pitch);
	}

	void MayaCamera::OnMouseButtonPressed(const MouseButtonEvent& event)
	{

	}

	void MayaCamera::OnMouseMoved(const MouseMovedEvent& event)
	{

	}

	void MayaCamera::OnKeyPressed(const KeyPressedEvent& event)
	{

	}

}