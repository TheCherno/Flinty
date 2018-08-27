#pragma once

#include <Flinty.h>

class SceneLayer : public fl::Layer
{
public:
	SceneLayer();
	~SceneLayer();

	void OnInit() override;

	void OnTick() override;
	void OnUpdate() override;
	void OnRender() override;
private:
	fl::Shader* m_Shader;
	fl::Shader* m_FullScreenQuadShader;
	fl::Framebuffer2D* m_Framebuffer;
	fl::Texture2D* m_RandTexture;

	fl::VertexArray* m_VertexArray;
	fl::VertexBuffer* m_VertexBuffer;
	fl::IndexBuffer* m_IndexBuffer;

	fl::MayaCamera m_Camera;
};
