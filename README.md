## D3D Engine을 공부하기 위한 프로젝트

- DirectX : 마이크로소프트 플랫폼에서 작업을 위한 API(application programming interface)의 집합\
Direct X Graphics Infrastructure(기반)\
-Adapter : 그래픽 카드 정보 열거\
-Output(모니터) : 디스플레이 모드 열거\
-Swap Chain  : 전면 버퍼와 후면 버퍼 바꿔가며 출력

 IA->VS->RS->PS->OM  (Direct3d graphics(Rendering)Pipeline 의 메인 5단계)
![1](https://user-images.githubusercontent.com/93506849/210162411-6491c609-512c-4a71-83d0-2e0f0ef4a821.png)
![2](https://user-images.githubusercontent.com/93506849/210162414-2a8d7c1c-a06a-4637-aa46-70b02858962c.png)
![3](https://user-images.githubusercontent.com/93506849/210162416-7e7a7b7f-6c47-48ac-a5b4-623449fd0841.png)\
출처 : https://m.blog.naver.com/jyh0841/220473615493

 * Input Assembler(IA)\
-Input Layout : 정점의 구성성분\
-Vertex Buffer : 정점의 실제 정보 / 배열처럼 내용을 순서대로 받음\
-Primitive Topology : 정점의 연결 방식\
-Index Buffer : 정점의 연결 순서

 * VS(Vertex Shader) : 각 정점에 대해 GPU에서 수행하는 사용자 정의(Vertex Shader) 함수

 * RS(Rasterizer Stage) : \
  Clipping : 출력영역에 포함되지 않은 내용을 소거하는 작업\
  Back Face Culling: 구성 방향이 반시계인 삼각형을 소거하는 작업\
   (시계->정면,반시계->뒷면으로 판단)\
  *안티앨리어싱: 레스터화(픽셀화)의 한계로 발생하는 계단현상을 억제해주는 기술\
  SSAA(Super-Sampling Anti Aliasing) : 강제적으로 배율을 높인 템플릿에 그린 뒤 원본사이즈로 줄인다.(현재는 사용안함)\
  MSAA(Multi-Sampling Anti Aliasing) : 경계면 색상을 그라데이션으로 계산하여 색을 채워준다.\
-Viewport 결합 가능\
 *View port\
projection : 3D-IA-VS-RS-2D의 랜더링 파이프라인을 통해 계산한다고 해도 우리가 사용하기 위해 리턴 받기가 힘들다 그래서 같은수식으로 계산해서 값을 사용하고,2D위치로 계산되어야 하는  UI 등을 표시하기 위해서 사용.\
unprojection : 2D공간에서 3D공간으로 이동하는것(마우스클릭을 위한 작용) 화면으로부터 지점까지의 삼각형에 선을그어 충돌 검사를 하는데 그사이에 물체를
	감지하면  그위치값을 반환을 한다.선의 시작 = 근면 마우스위치, 선의 종료 = 원면 마우스 위치 선의 방향 = 선의시작-선의 종료/대형 맵에 관해서는 '스크린스페이스 피킹방법'이 있다.\
![hFOV to vFOV](https://user-images.githubusercontent.com/93506849/166220045-471e5f18-2170-4c00-bf25-b1dc720ebe18.png)
\
버퍼 와 텍스처가 DX의 자원 (Resource)
> + Texture : 2차원 데이터, 어떤 의미를 가지고 있는 데이터인지 바로 알기 힘들다는 단점을 가지고 있음
  -SRV (Shader Resource View) : 셰이더에서 텍스쳐를 자원으로 쓰겠다는 관점 
  -RTV (Render Target View) : 텍스쳐를 렌더 대상으로 보겠단 관점 
  -DSV (Depth-Stencil View) :  3차원에서 사용하는 내용
  -UAV (Unordered Access View) : 순서 없는 접근
  ![텍스처](https://user-images.githubusercontent.com/93506849/165050345-e6992aaf-a3ba-4e8e-98cc-b07bb6227bb7.JPG)
  
>  + Buffer\
  -VertexBuffer : 정점들로 조립되어서 렌더링 파이프라인에 투입될 자료를 담는 역할을 한다. 가장 단순한 형태의 정점 버퍼는 정점 구조체들의 배열이다. 그러한 배열의 각 원소는 정점의 위치, 법선 벡터, 텍스처 좌표 같은 자료를 담는다\
  -IndexBuffer : 정점의 연결순서를 저장하여 도형을 정의하는 기능을 담당한다.\
-CS Buffer\
Direct Compute : 다이렉트x라이브러리 / 그래픽카드를 코딩하기 위한 언어체계
		대량으로 있는 데이터를 쪼개질 수 있게 하기위해 필요하다. GPU가 다량의 쓰레드를 사용한다.
	 -Comput Shader는 계산용으로만 사용되므로 렌더링 파이프라인과 별도로 동작하며, 따로 설정이 가능하다\
	 -RawBuffer-ByteAddress : 바이트 단위로 CS에서다루게 되는 버퍼\
	 -Texture2DBuffer : 2차원 배열을 CS에서 사용할 수 있도록 해주는 버퍼\
	 -StruturedBuffer : 구조체를 CS로 넘겨 구조체 단위로 사용

 * PS(Pixel Shader Stage) : 각 픽셀에 대해 GPU에서 사용자 정의 함수를 수행하는 단계\
-Vertex에 색상을 입력한다.

 * Output Merger(OM) : Render Target View/결과를 출력할 대상 일반적으로 Swap Chain의 Scareen Buffer를 대상으로 함.



# 구현기능
- Mesh & Texture
![매시](https://user-images.githubusercontent.com/93506849/166215380-2f7a3a23-e36e-4fc2-94c9-f5ce3fe126a3.JPG)

- 조명 효과(Meterial)\
 -Ambient : 태양, 실내에서 주 사용빛(Main Light)\
 -Diffuse(Lambert) : 자기가 가지고 있는 색상(음영도 포함)\
 -Specular(Phong) : 정반사광\
 -Emissive : 외곽선의 색을 표시하는 부분 =시각과 노멀백터에 의존함(아웃라인쉐이딩에 많이 사용함).
 ![빛](https://user-images.githubusercontent.com/93506849/165054425-eabae885-1037-4491-8d05-3a397781ce7c.JPG)

- Particle :날씨등 입자를 불규칙적으로 움직이게 하는걸 통틀어 표현/일반적인 엔진들은 통합처리되어있음.\
![비](https://user-images.githubusercontent.com/93506849/166085134-94b2bd2d-cc6d-4a33-b700-dac700464cee.gif)
![눈](https://user-images.githubusercontent.com/93506849/166085147-99ad4ae7-8987-4d45-8861-1a89ce65676a.gif)


- MultiRenderTarget \
한번의 픽셀 셰이더 렌더링으로 여러개의 장면을 얻어내는 방법\
-posteffect : 뽀샤시, 혈흔 등 효과를 내는 effect\
-Blur : 픽셀을 고의적으로 망가트려 뿌연효과를 만드는 방법
-Gaussian Blur 게임에서 흔히 사용되는 블러방식, 가우스 함수를 이용해 계산한 블러 횟수 당 가중치를 곱한방식
![165056088-30eeeab9-bcbe-4e71-83a0-4b6e7e03e445](https://user-images.githubusercontent.com/93506849/166214637-916cd5f3-2369-4404-a472-32a0700ab328.jpg)
![세피아](https://user-images.githubusercontent.com/93506849/166214655-eaa88894-6852-4760-a3d8-e3703ef862b9.JPG)


- Normal Mapping : 평면에 굴곡이있는 면을넣어 입체감을 만들게함. 사람이 입체감을 느끼게 되는것은 음영이 있기 때문이다. 노멀맵은 픽셀의 값을 방향으로 변환하여 노멀백터로 간주해 라이팅과의 내적으로 음영을만든다.\
	=BumpMapping, 페럴럭스 오큘리전\
  탄잰트공간 : 이미지에서 가져온값(RGB)으로 백터를만들고 이 값들로과 조명값과 내적\
	(텍스처 -> RGB -> 0~1 -> xyz) 노멀맵은 바깥쪽으로 나오는색이 많으므로 파란색으로 많이나온다. \
	Z : Normal\
	X : U - Tangent\
	Y : V - BiNormal or BiTangent 외적을 어느쪽으로하냐에따라 달라짐.
![노말맵](https://user-images.githubusercontent.com/93506849/166212991-28081c94-7781-4b7f-9320-637e08c929c9.jpg)


- Geometry Shader :VertexShader를 거쳐온 도형 정보를 입력받는데, 해당 도형 정보의 정점을 모두 없앨 수도있고 더 많은 도형을 만들어 내보낼 수 있다.\
-DynamicCubeMap\
![1](https://user-images.githubusercontent.com/93506849/166083570-1482fe73-df86-4acd-a770-b728bd2e659c.JPG)\
-Billboard\
![빌보드](https://user-images.githubusercontent.com/93506849/165087939-3ed08ae1-45d8-40aa-b303-630cd00777ec.JPG)\
-Shadow\
![그림자1](https://user-images.githubusercontent.com/93506849/166084212-3bddbfb6-c968-4fd1-9124-53530b6cae9b.JPG)




# 추가 소스 모음 : https://github.com/rokMkiaz/ProjectResourceFile
