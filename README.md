D3D Engine을 만들기 위한 프로젝트


조명
 Ambient : 태양, 실내에서 주 사용빛(Main Light)
 Diffuse(Lambert) : 자기가 가지고 있는 색상(음영도 포함)
 Specular(Phong) : 정반사광
 Emissive : 외곽선의 색을 표시하는 부분 =시각과 노멀백터에 의존함(아웃라인쉐이딩에 많이 사용함).
 ![빛](https://user-images.githubusercontent.com/93506849/165054425-eabae885-1037-4491-8d05-3a397781ce7c.JPG)

 
 
  Normal Mapping : 평면에 굴곡이있는 면을넣어 입체감을 만들게함. 사람이 입체감을 느끼게 되는것은 음영이 있기 때문이다. 노멀맵은 픽셀의 값을 방향으로 변환하여 노멀백터로 간주해 라이팅과의 내적으로 음영을만든다.
	=BumpMapping, 페럴럭스 오큘리전
  탄잰트공간 : 이미지에서 가져온값(RGB)으로 백터를만들고 이 값들로과 조명값과 내적
	(텍스처 -> RGB -> 0~1 -> xyz) 노멀맵은 바깥쪽으로 나오는색이 많으므로 파란색으로 많이나온다. 
	Z : Normal
	X : U - Tangent
	Y : V - BiNormal or BiTangent 외적을 어느쪽으로하냐에따라 달라짐.
![노말맵1](https://user-images.githubusercontent.com/93506849/165054476-0486f0aa-d3df-4deb-bffc-af9d49b388bb.JPG)
  ![노말맵2](https://user-images.githubusercontent.com/93506849/165054706-e7993c3f-f705-4343-b2db-1c1ae03401f6.JPG)
  ![노말맵4](https://user-images.githubusercontent.com/93506849/165054731-5381731f-2ea8-43e8-a62a-10c408633422.JPG)



모델링

Tweening = 애니매이션 동작의 구간값을 구해 섞어 자연스럽게 이어지게 한다.
Blending = 애니매이션의 동작을 섞어 자연스럽게 구현하는방법.

CS Buffer
Direct Compute : 다이렉트x라이브러리 / 그래픽카드를 코딩하기 위한 언어체계
		대량으로 있는 데이터를 쪼개질 수 있게 하기위해 필요하다. GPU가 다량의 쓰레드를 사용한다.
	-Comput Shader는 계산용으로만 사용되므로 렌더링 파이프라인과 별도로 동작하며, 따로 설정이 가능하다
	-RawBuffer-ByteAddress : 바이트 단위로 CS에서다루게 되는 버퍼
	-Texture2DBuffer : 2차원 배열을 CS에서 사용할 수 있도록 해주는 버퍼
	-StruturedBuffer : 구조체를 CS로 넘겨 구조체 단위로 사용






Direct X Graphics Infrastructure(기반)
-Adapter : 그래픽 카드 정보 열거
-Output(모니터) : 디스플레이 모드 열거
-Swap Chain  : 전면 버퍼와 후면 버퍼 바꿔가며 출력

IA->VS->RS->PS->OM  (Direct3d graphics(Rendering)Pipeline 의 5단계)
 
Input Assembler(IA)/
-Input Layout : 정점의 구성성분
-Vertex Buffer : 정점의 실제 정보 / 배열처럼 내용을 순서대로 받음
-Primitive Topology : 정점의 연결 방식
-Index Buffer : 정점의 연결 순서

VS(Vertex Shader) : 각 정점에 대해 GPU에서 수행하는 사용자 정의(Vertex Shader) 함수

RS(Rasterizer Stage) : 
  Clipping : 출력영역에 포함되지 않은 내용을 소거하는 작업
  Back Face Culling: 구성 방향이 반시계인 삼각형을 소거하는 작업
   (시계->정면,반시계->뒷면으로 판단)
  *안티앨리어싱: 레스터화(픽셀화)의 한계로 발생하는 계단현상을 억제해주는 기술
  SSAA(Super-Sampling Anti Aliasing) : 강제적으로 배율을 높인 템플릿에 그린 뒤 원본사이즈로 줄인다.(현재는 사용안함)
  MSAA(Multi-Sampling Anti Aliasing) : 경계면 색상을 그라데이션으로 계산하여 색을 채워준다.
-Viewport 결합 가능
 *View port 
projection : 3D-IA-VS-RS-2D의 랜더링 파이프라인을 통해 계산한다고 해도 우리가 사용하기 위해 리턴 받기가 힘들다 그래서 같은수식으로 계산해서 값을 사용하고,
	2D위치로 계산되어야 하는  UI 등을 표시하기 위해서 사용.
unprojection : 2D공간에서 3D공간으로 이동하는것(마우스클릭을 위한 작용) 화면으로부터 지점까지의 삼각형에 선을그어 충돌 검사를 하는데 그사이에 물체를
	감지하면  그위치값을 반환을 한다.선의 시작 = 근면 마우스위치, 선의 종료 = 원면 마우스 위치 선의 방향 = 선의시작-선의 종료/대형 맵에 관해서는 '스크린스페이스 피킹방법'이 있다.
aabb(Axis Aligne Bounding Box) : 사각형이 회전되어있지 않은 상태의 충돌 상태
obb(Oriented Bounding Box) : 회전 적용된 상태의 충돌
	Slab  : 어떤 축 두개를 연장했을 대 두 축 사이의 무한한 공간 obb는 슬랩의 영역에 선분이 교차하는지 체크하는 방법
충돌에서는 15개의 분리축이 되는지아닌지를 확인
  텍스처 맵핑 - 실제 택스처로부터 색상을 1픽셀단위로 가져옴


버퍼 와 텍스처가 DX의 자원 (리소스)
Texture : 2차원 데이터, 어떤 의미를 가지고 있는 데이터인지 바로 알기 힘들다는 단점을 가지고 있음
  - SRV (Shader Resource View) : 셰이더에서 텍스쳐를 자원으로 쓰겠다는 관점 
  - RTV (Render Target View) : 텍스쳐를 렌더 대상으로 보겠단 관점 
  - DSV (Depth-Stencil View) :  3차원에서 사용하는 내용
  - UAV (Unordered Access View) : 순서 없는 접근
  -  ![텍스처](https://user-images.githubusercontent.com/93506849/165050345-e6992aaf-a3ba-4e8e-98cc-b07bb6227bb7.JPG)

노멀맵핑,

PS(Pixel Shader Stage) : 각 픽셀에 대해 GPU에서 사용자 정의 함수를 수행하는 단계
-PS에서 찍은걸 그대로 RTV에 찍는다

