#pragma once
inline DWORD process_id;
inline HANDLE handle;
inline uintptr_t ReplayInterfacePointer;
inline uintptr_t CPedFactoryPointer;
inline uintptr_t CViewportGamePointer;
inline uintptr_t WindowWidth;
inline uintptr_t camGameplayDirectorPointer;
inline uintptr_t CNetworkPlayerMgrPointer;

// CAutomobile : CVehicle : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// fragInstGta : rage::phfwFragInst : rage::fragInst : rage::phInstBreakable : rage::phInst : rage::pgBase
// CPed : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// phInstGta : rage::phfwInst : rage::phInst : rage::pgBase
// CPickup : CObject : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// phInstGta : rage::phfwInst : rage::phInst : rage::pgBase
// CObject : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// phInstGta : rage::phfwInst : rage::phInst : rage::pgBase
// CPedFactory
// CPed : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CViewportGame : CViewport
// CViewportPrimaryOrtho : CViewport
// CViewportFrontend3DScene : CViewport
// camGameplayDirector : camBaseDirector : camBaseObject : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// camFollowPedCamera : camFollowCamera : camThirdPersonCamera : camBaseCamera : camBaseObject : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CNetworkPlayerMgr : rage::netPlayerMgrBase
// CNetGamePlayer : rage::netPlayer
// CPlayerInfo : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CPed : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase

// Model Coordinates
// World Coordinates
// Camera (View) Coordinates
// Clip Coordinates
// Image Coordinates

// Model Matrix (Model Coordinates -> World Coordinates)
// View Matrix (World Coordinates -> Camera (View) Coordinates)
// Projection Matrix (Camera (View) Coordinates -> Clip Coordinates)

// Local Space (Object Space)
// World Space
// View Space (Eye Space)
// Clip Space
// Screen Space

inline int window_width;
inline int window_height;
inline uintptr_t CViewportGame;
inline float matrix[16];
inline uintptr_t local_cped;
inline uintptr_t camFollowPedCamera;

inline uintptr_t CReplayInterfaceVeh;
inline uintptr_t CAutombileList;
inline int CAutombileMaxCount;
inline int CAutombileCurrentCount;
inline std::vector<Automobile> automobiles;

inline uintptr_t CReplayInterfacePed;
inline uintptr_t CPedList;
inline int CPedMaxCount;
inline int CPedCurrentCount;
inline std::vector<Ped> peds;

inline uintptr_t CReplayInterfacePickup;
inline uintptr_t CPickupList;
inline int CPickupMaxCount;
inline int CPickupCurrentCount;
inline std::vector<Pickup> pickups;

inline uintptr_t CReplayInterfaceObject;
inline uintptr_t CObjectList;
inline int CObjectMaxCount;
inline int CObjectCurrentCount;
inline std::vector<Object> objects;

inline std::vector<Player> players;