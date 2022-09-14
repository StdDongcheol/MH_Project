
#pragma once

enum class Engine_Space
{
	Space2D,
	Space3D
};

enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX
};

enum class Buffer_Type
{
	Vertex,
	Index
};

enum class Shader_Type
{
	Graphic,
	Compute
};

enum class Buffer_Shader_Type
{
	Vertex = 0x1,
	Pixel = 0x2,
	Domain = 0x4,
	Hull = 0x8,
	Geometry = 0x10,
	Compute = 0x20,
	Graphic = Vertex | Pixel | Domain | Hull | Geometry,
	All = Vertex | Pixel | Domain | Hull | Geometry | Compute
};

enum class Component_Type
{
	SceneComponent,
	ObjectComponent
};

enum class Input_Type
{
	Direct,
	Window
};

enum Key_State
{
	KeyState_Down,
	KeyState_Push,
	KeyState_Up,
	KeyState_Max
};

enum class Image_Type
{
	Atlas,
	Frame,
	Array,
	RenderTarget
};

enum class Sampler_Type
{
	Point,
	Linear,
	Anisotropic
};

enum class RenderState_Type
{
	Blend,
	Rasterizer,
	DepthStencil,
	Max
};

enum class SceneComponent_Type
{
	Sprite,
	StaticMesh,
	Box2D,
	Circle,
	Pixel,
	Camera,
	Widget,
	Particle,
	TileMap,
	Max
};

enum class Collision_Channel
{
	Object,
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
	Environment,
	Carving,
	MonsterSpot,
	FieldObj,
	MonsterSliding,
	PlayerSliding,
	NPC,
	Custom8,
	Custom9,
	Custom10,
	Custom11,
	Custom12,
	Custom13,
	Custom14,
	Custom15,
	Custom16,
	Max
};

enum class Collision_Interaction
{
	Ignore,
	Collision
};

enum class Collision_State
{
	Begin,
	End,
	Max
};

enum class Collider_Type
{
	Box2D,
	Circle,
	Pixel,
	Sphere,
	Box3D
};

enum class Camera_Type
{
	Camera2D,
	Camera3D,
	CameraUI
};

enum class PixelCollision_Type
{
	Color_Ignore,
	Color_Confirm,
	Alpha_Ignore,
	Alpha_Confirm
};

enum class Button_State
{
	Normal,
	MouseOn,
	Click,
	Disable,
	Max
};

enum class Button_Sound_State
{
	MouseOn,
	Click,
	Max
};

enum class WidgetComponent_Space
{
	Screen,
	World
};

enum class ProgressBar_Dir
{
	RightToLeft,
	LeftToRight,
	TopToBottom,
	BottomToTop
};

enum class Mouse_State
{
	Normal,
	Click,
	State2,
	State3,
	State4,
	State5,
	State6,
	State7,
	State8,
	State9,
	State10,
	Max
};

enum class Tile_Shape
{
	Rect,
	Rhombus,
	End
};

enum class Tile_Type
{
	Normal,
	Wall,
	End
};

enum class Nav_Node_Type
{
	None,
	Open,
	Close
};

enum class Mesh_Type
{
	Sprite,
	Static,
	Animation
};

enum class Light_Type
{
	Dir,
	Point,
	Spot,
	End
};

enum class Transform_State
{
	None,
	Ground,
	Falling
};

enum class Object_Type
{
	Player,
	Monster,
	LandScape,
	FieldObj,
	Max
};

enum class Monster_Type
{
	Barnos,
	Jagras,
	Kestodon,
	Vespoid,
	Anjanath,
	Rathalos,
	Max
};

enum class FieldObj_Type
{
	SlidingBox,
	HealFlower,
	SmallTree,
	Tree,
	BigTree,
	BrokenTree,
	MushRoom,
	SmallGrass,
	Grass,
	Vine,
	Precipice,
	Sculpture,
	SmallStone,
	GrassRock,
	Wreck,
	Tent,
	Box,
	Far,
	Stone,
	TownBarrel,
	TownCarriage,
	TownCheckPoint,
	TownDragonHead,
	TownPassage,
	TownPumpkinMan,
	TownRampart,
	TownShadeScreen,
	TownSign,
	TownStructure,
	TownSummerHouse,
	TownTunnel,
	DesertPebble,
	DesertSmallStone,
	DesertStone,
	DesertBigStone,
	DesertRockWall,
	DesertStalactite,
	DesertStalagmite,
	DesertMountain,
	Max
};
 
enum class Brush_Type
{
	None,
	Circle,
	Rect
};

enum class Widget_Fade_State
{
	FadeIn,
	FadeOut,
	Duration,
	Max
};

enum class BrushEdit_Type
{
	Height,
	Splatting
};

enum class NavAgent_Type
{
	Nav2D,
	Nav3D
};

enum class LandScape_TextureType
{
	Grass,
	Sand,
	Rock
};

enum class Coating_State
{
	None,
	Normal,
	Strong,
	Explosion
};

enum class Monster_Name
{
	None,
	Barnos,
	Jagras,
	Kestodon,
	Vespoid,
	Anjanath,
	Rathalos,
	End
};

enum class Check_Type
{
	None,
	StageToLoading,
	LoadingToStage,
	End
};

enum class Stage_Type
{
	None,
	Town,
	Stage1,
	Stage2
};

enum class BGM_Type
{
	None,
	MonsterBattle,
	MonsterKilled,
	BossBattle,
	QuestComplete,
	FinalBossBattle,
	FinalQuestComplete
};

enum class Box_Type
{
	Cube,
	Cuboid
};