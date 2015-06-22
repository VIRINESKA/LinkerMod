#pragma once

#ifdef D3DBSP_LIB_EXPORTS
#define D3DBSP_LIB_API __declspec(dllexport)
#else
#define D3DBSP_LIB_API __declspec(dllimport)
#endif

enum LOGFILE_MODE
{
	LOGFILE_READ_ONLY,
	LOGFILE_OVERWRITE,
	LOGFILE_APPEND,
	LOGFILE_UPDATE,
	LOGFILE_UPDATE_OVERWRITE,
	LOGFILE_UPDATE_APPEND
};

int D3DBSP_LIB_API Con_Init(void);
int D3DBSP_LIB_API Con_Init(const char* logfilePath, LOGFILE_MODE mode);
int D3DBSP_LIB_API Log_Init(const char* logfilePath, LOGFILE_MODE mode);
int D3DBSP_LIB_API Con_Printf(const char* fmt, ...);
int D3DBSP_LIB_API Con_Warning(const char* fmt, ...);
int D3DBSP_LIB_API Con_Error(const char* fmt, ...);
int D3DBSP_LIB_API Log_Printf(const char* fmt, ...);
DWORD D3DBSP_LIB_API Con_ErrorCount(void);
DWORD D3DBSP_LIB_API Con_WarningCount(void);
int D3DBSP_LIB_API Con_Restore(void);

class D3DBSP_LIB_API Lump
{
public:
	bool isEmpty;
	BYTE* content;
	size_t size;

	Lump& operator=(Lump&);

	BYTE* AllocateMemory(size_t size);
	void FreeMemory(void);

	Lump(void);
	Lump(const Lump&);
	~Lump(void);
};

enum LUMP_TYPE : DWORD
{
  LUMP_MATERIALS = 0x0,
  LUMP_LIGHTBYTES = 0x1,
  LUMP_LIGHTGRIDENTRIES = 0x2,
  LUMP_LIGHTGRIDCOLORS = 0x3,
  LUMP_PLANES = 0x4,
  LUMP_BRUSHSIDES = 0x5,
  LUMP_BRUSHSIDEEDGECOUNTS = 0x6,
  LUMP_BRUSHEDGES = 0x7,
  LUMP_BRUSHES = 0x8,
  LUMP_TRIANGLES = 0x9,
  LUMP_DRAWVERTS = 0xA,
  LUMP_DRAWINDICES = 0xB,
  LUMP_CULLGROUPS = 0xC,
  LUMP_CULLGROUPINDICES = 0xD,
  LUMP_OBSOLETE_1 = 0xE,
  LUMP_OBSOLETE_2 = 0xF,
  LUMP_OBSOLETE_3 = 0x10,
  LUMP_OBSOLETE_4 = 0x11,
  LUMP_OBSOLETE_5 = 0x12,
  LUMP_PORTALVERTS = 0x13,
  LUMP_OBSOLETE_6 = 0x14,
  LUMP_UINDS = 0x15,
  LUMP_BRUSHVERTSCOUNTS = 0x16,
  LUMP_BRUSHVERTS = 0x17,
  LUMP_AABBTREES = 0x18,
  LUMP_CELLS = 0x19,
  LUMP_PORTALS = 0x1A,
  LUMP_NODES = 0x1B,
  LUMP_LEAFS = 0x1C,
  LUMP_LEAFBRUSHES = 0x1D,
  LUMP_LEAFSURFACES = 0x1E,
  LUMP_COLLISIONVERTS = 0x1F,
  LUMP_COLLISIONTRIS = 0x20,
  LUMP_COLLISIONEDGEWALKABLE = 0x21,
  LUMP_COLLISIONBORDERS = 0x22,
  LUMP_COLLISIONPARTITIONS = 0x23,
  LUMP_COLLISIONAABBS = 0x24,
  LUMP_MODELS = 0x25,
  LUMP_VISIBILITY = 0x26,
  LUMP_ENTITIES = 0x27,
  LUMP_PATHCONNECTIONS = 0x28,
  LUMP_REFLECTION_PROBES = 0x29,
  LUMP_VERTEX_LAYER_DATA = 0x2A,
  LUMP_PRIMARY_LIGHTS = 0x2B,
  LUMP_LIGHTGRIDHEADER = 0x2C,
  LUMP_LIGHTGRIDROWS = 0x2D,
  LUMP_OBSOLETE_10 = 0x2E,

  //Obsolete in BO1/////////////////
  LUMP_UNLAYERED_TRIANGLES = 0x2F,
  LUMP_UNLAYERED_DRAWVERTS = 0x30,
  LUMP_UNLAYERED_DRAWINDICES = 0x31,
  LUMP_UNLAYERED_CULLGROUPS = 0x32,
  LUMP_UNLAYERED_AABBTREES = 0x33,
  //////////////////////////////////

  LUMP_WATERHEADER = 0x34,
  LUMP_WATERCELLS = 0x35,
  LUMP_WATERCELLDATA = 0x36,
  LUMP_BURNABLEHEADER = 0x37,
  LUMP_BURNABLECELLS = 0x38,
  LUMP_BURNABLECELLDATA = 0x39,
  LUMP_SIMPLELIGHTMAPBYTES = 0x3A,
  LUMP_LODCHAINS = 0x3B,
  LUMP_LODINFOS = 0x3C,
  LUMP_LODSURFACES = 0x3D,
  LUMP_LIGHTREGIONS = 0x3E,
  LUMP_LIGHTREGION_HULLS = 0x3F,
  LUMP_LIGHTREGION_AXES = 0x40,
  LUMP_WIILIGHTGRID = 0x41,
  LUMP_LIGHTGRID2D_LIGHTS = 0x42,
  LUMP_LIGHTGRID2D_INDICES = 0x43,
  LUMP_LIGHTGRID2D_POINTS = 0x44,
  LUMP_LIGHTGRID2D_CELLS = 0x45,
  LUMP_LIGHT_CORONAS = 0x46,

  //BO Specific/////////////////////////
  LUMP_SHADOWMAP_VOLUMES = 0x47,
  LUMP_SHADOWMAP_VOLUME_PLANES = 0x48,
  LUMP_EXPOSURE_VOLUMES = 0x49,
  LUMP_EXPOSURE_VOLUME_PLANES = 0x4A,
  LUMP_OCCLUDERS = 0x4B,
  LUMP_OUTDOORBOUNDS = 0x4C,
  LUMP_HERO_ONLY_LIGHTS = 0x4D,
  //////////////////////////////////////

  INFO_LUMP_TYPE_COUNT
};

enum BSPVERSION_TYPE
{
	BSPVERSION_COD_WAW = 31,
	BSPVERSION_COD_BO = 45
};

class D3DBSP_LIB_API D3DBSP
{
public:
	DWORD diskLumpCount;

	DWORD diskLumpOrderSize;
	LUMP_TYPE* diskLumpOrder;

	DWORD bspVersion;
	Lump lumps[INFO_LUMP_TYPE_COUNT];

	int Load(const char* filepath);
	int Write(const char* filepath);

	int ConvertFrom(D3DBSP*, BSPVERSION_TYPE);

	D3DBSP(void);
	~D3DBSP(void);
};
