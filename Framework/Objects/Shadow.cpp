#include"Framework.h"
#include"Shadow.h"

Shadow::Shadow(Shader* shader, Vector3& position, float radius, UINT width, UINT height)
	: shader(shader), position(position), radius(radius), width(width), height(height)
{
	renderTarget = new RenderTarget(width, height);
	depthStencil = new DepthStencil(width, height);
	viewport = new Viewport((float)width, (float)height);


	desc.MapSize = Vector2((float)width, (float)height); //한픽셀 크기 찾는

	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Shadow");
	sShadowMap = shader->AsSRV("ShadowMap");

	//Create Sampler State
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
		desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR; //깊이비교+샘플링 필터 옵션
		desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL; //작거나 같은 깊이 통과
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.MaxAnisotropy = 1;
		desc.MaxLOD = FLT_MAX;

		Check(D3D::GetDevice()->CreateSamplerState(&desc, &pcfSampler));
		sPcfSampler = shader->AsSampler("ShadowSampler");
	}
}

Shadow::~Shadow()
{
	SafeDelete(renderTarget);
	SafeDelete(depthStencil);
	SafeDelete(viewport);

	SafeDelete(buffer);
}

void Shadow::PreRender()
{

	ImGui::InputInt("Quality", (int*)&desc.Quality);
	desc.Quality %= 3;

	
	ImGui::Separator();
	//1Pass Test
	ImGui::SliderFloat3("Light Direction", Context::Get()->Direction(), -1, +1);
	ImGui::SliderFloat("Bias", &desc.Bias, -0.0001f, +0.01f, "%.4f");

	renderTarget->PreRender(depthStencil);
	viewport->RSSetViewport();


	CalcViewProjection();

	buffer->Render();
	sBuffer->SetConstantBuffer(buffer->Buffer());

	sShadowMap->SetResource(depthStencil->SRV());
	sPcfSampler->SetSampler(0, pcfSampler);
}

void Shadow::CalcViewProjection()
{
	Vector3 up = Vector3(0, 1, 0);
	Vector3 direction = Context::Get()->Direction();
	Vector3 position = direction * radius * -2.0f;

	D3DXMatrixLookAtLH(&desc.View, &position, &this->position, &up);

	Vector3 origin;
	D3DXVec3TransformCoord(&origin, &this->position, &desc.View);

	float l = origin.x - radius;
	float b = origin.y - radius;
	float n = origin.z - radius;

	float r = origin.x + radius;
	float t = origin.y + radius;
	float f = origin.z + radius;

	D3DXMatrixOrthoLH(&desc.Projection, r - l, t - b, n, f);
}
