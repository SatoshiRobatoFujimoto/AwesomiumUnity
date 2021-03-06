// Check out http://docs.unity3d.com/Documentation/Manual/NativePluginInterface.html
// for additional documentation about this process.

#include "UnityPlugin.h"
#include "GraphicsInclude.h"

void* g_GraphicsDevice = 0;
int g_GraphicsDeviceType = -1;
#if SUPPORT_D3D9
IDirect3DDevice9* g_D3D9GraphicsDevice = 0;
#endif
#if SUPPORT_D3D11
ID3D11Device* g_D3D11GraphicsDevice = 0;
#endif

static void DebugLog (const char* str)
{
#if UNITY_WIN
	OutputDebugStringA (str);
#else
	printf ("%s", str);
#endif
}

// If exported by a plugin, this function will be called when graphics device is created, destroyed,
// and before and after it is reset (ie, resolution changed).
extern "C" void EXPORT_API UnitySetGraphicsDevice( void* device, int deviceType, int eventType )
{
	// Assign default values.
	g_GraphicsDevice = 0;
	g_GraphicsDeviceType = -1;

	switch (eventType)
	{
	case kGfxDeviceEventInitialize:
	case kGfxDeviceEventAfterReset:
		{
			g_GraphicsDevice = device;
			g_GraphicsDeviceType = deviceType;

			switch (g_GraphicsDeviceType)
			{
			case kGfxRendererD3D9:
				{
					DebugLog ("Set D3D9 graphics device\n");
					g_D3D9GraphicsDevice = (IDirect3DDevice9*)g_GraphicsDevice;
					break;
				}
			case kGfxRendererD3D11:
				{
					DebugLog ("Set D3D11 graphics device\n");
					g_D3D11GraphicsDevice = (ID3D11Device*)g_GraphicsDevice;
					break;
				}
			case kGfxRendererOpenGL:
				{
					DebugLog ("Set OpenGL graphics device\n");
					break;
				}
			}
			break;
		}
	case kGfxDeviceEventBeforeReset:
		{
			break;
		}
	case kGfxDeviceEventShutdown:
		{
			break;
		}
	}
}

// If exported by a plugin, this function will be called for GL.IssuePluginEvent script calls.
// The function will be called on a rendering thread; note that when multithreaded rendering is used,
// the rendering thread WILL BE DIFFERENT from the thread that all scripts & other game logic happens!
// You have to ensure any synchronization with other plugin script calls is properly done by you.
extern "C" void EXPORT_API UnityRenderEvent ( int eventID )
{

}


void* GetBufferPtrFromNativePtr( void* _NativePtr )
{

	return 0;
}