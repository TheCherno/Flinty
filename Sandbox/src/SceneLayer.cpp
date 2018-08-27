#include "SceneLayer.h"

using namespace fl;

SceneLayer::SceneLayer()
	: Layer("Scene"), m_Camera(math::mat4::Perspective(65.0f, 16.0f/9.0f, 0.001f, 10000.0f))
{
}

SceneLayer::~SceneLayer()
{
}

void SceneLayer::OnInit()
{
	Application& app = Application::Get();

	m_Shader = ShaderFactory::SimpleShader();
	ShaderManager::Add(m_Shader);
	m_Shader->Bind();
	m_Shader->SetUniform("pr_matrix", math::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	m_FullScreenQuadShader = ShaderFactory::FullScreenQuadShader();
	ShaderManager::Add(m_FullScreenQuadShader);

	float vertices[] = {
		-8.5f, -8.5f, 0.0f, 0.0f, 1.0f,
		-8.5f,  8.5f, 0.0f, 0.0f, 0.0f,
		8.5f,  8.5f, 0.0f, 1.0f, 0.0f,
		8.5f, -8.5f, 0.0f, 1.0f, 1.0f
	};

	uint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	int* pixels = new int[64 * 64];
	for (int i = 0; i < 64 * 64; i++)
		pixels[i] = 0xff0000ff + i * 256;

	m_RandTexture = AssetManager::CreateTexture<Texture2D>(TextureFormat::RGBA, 64, 64);
	m_RandTexture->SetData(pixels);

	Texture2D* fbColor = AssetManager::CreateTexture<Texture2D>(TextureFormat::RGBA, app.GetWidth(), app.GetHeight());
	m_Framebuffer = new Framebuffer2D(app.GetWidth(), app.GetHeight());
	m_Framebuffer->AttachColor(fbColor);

	m_VertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
	m_IndexBuffer = new IndexBuffer(indices, 6);

	VertexBufferLayout layout;
	layout.Push<math::vec3>("position");
	layout.Push<math::vec2>("texcoord");
	m_VertexBuffer->SetLayout(layout);

	m_VertexArray = new VertexArray(m_VertexBuffer, m_IndexBuffer);
}

void SceneLayer::OnTick()
{

}

void SceneLayer::OnUpdate()
{
	m_Camera.Update();
}

void SceneLayer::OnRender()
{
	Renderer& renderer = Renderer::Get();
	renderer.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	renderer.Clear();

	m_Shader->Bind();
	m_Shader->SetUniform("pr_matrix", m_Camera.GetProjectionMatrix() *  m_Camera.GetViewMatrix());

	m_Framebuffer->Bind();
	renderer.Clear();
	m_RandTexture->Bind();

	renderer.Draw(m_VertexArray, m_Shader);

	m_Framebuffer->Unbind();

	m_Framebuffer->GetColorAttachment()->Bind();
	renderer.DrawFullScreenQuad(m_FullScreenQuadShader);
}