#include <Flinty.h>

#include <iostream>
#include <fl/gl.h>

using namespace fl;

static Window* s_Window;
static Shader* s_Shader;
static Shader* s_FullScreenQuadShader;
static Framebuffer2D* s_Framebuffer;
static Texture2D* s_RandTexture;

static VertexArray* s_VertexArray;
static VertexBuffer* s_VertexBuffer;
static IndexBuffer* s_IndexBuffer;

static void OnUpdate()
{
}

static void OnRender(Renderer& renderer)
{
	renderer.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	s_Framebuffer->Bind();
	s_RandTexture->Bind();

	renderer.Draw(s_VertexArray, s_Shader);

	s_Framebuffer->Unbind();

	s_Framebuffer->GetColorAttachment()->Bind();
	renderer.DrawFullScreenQuad(s_FullScreenQuadShader);
}

static void OnKeyEvent(int key, int action)
{
}

int main()
{
	Window window("Sandbox", 1280, 720);
	s_Window = &window;

	window.SetUpdateCallback(OnUpdate);
	window.SetRenderCallback(OnRender);
	window.SetKeyCallback(OnKeyEvent);

	AssetManager::Init();

	s_Shader = ShaderFactory::SimpleShader();
	ShaderManager::Add(s_Shader);
	s_Shader->Bind();
	s_Shader->SetUniform("pr_matrix", maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	s_FullScreenQuadShader = ShaderFactory::FullScreenQuadShader();
	ShaderManager::Add(s_FullScreenQuadShader);

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

	s_RandTexture = AssetManager::CreateTexture<Texture2D>(TextureFormat::RGBA, 64, 64);
	s_RandTexture->SetData(pixels);

	Texture2D* fbColor = AssetManager::CreateTexture<Texture2D>(TextureFormat::RGBA, window.GetWidth(), window.GetHeight());
	s_Framebuffer = new Framebuffer2D(window.GetWidth(), window.GetHeight());
	s_Framebuffer->AttachColor(fbColor);
	
	s_VertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
	s_IndexBuffer = new IndexBuffer(indices, 6);

	VertexBufferLayout layout;
	layout.Push<maths::vec3>("position");
	layout.Push<maths::vec2>("texcoord");
	s_VertexBuffer->SetLayout(layout);

	s_VertexArray = new VertexArray(s_VertexBuffer, s_IndexBuffer);

	window.Show();
	return 0;
}