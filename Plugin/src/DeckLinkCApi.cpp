#include "DeckLinkCApi.hpp"
#include "DeckLinkInputStream.hpp"
#include "DeckLinkManager.hpp"
#include "DeckLinkOutputStream.hpp"
#include "DeckLinkVideoFrame.hpp"
#include <DeckLinkAPI.h>
#include <DeckLinkAPIVersion.h>

int DeckLink_GetVersion() { return BLACKMAGIC_DECKLINK_API_VERSION; }

const char *DeckLink_GetVersionString() {
  return BLACKMAGIC_DECKLINK_API_VERSION_STRING;
}

void DeckLink_AddRef(void *obj) { ((IUnknown *)obj)->AddRef(); }

void DeckLink_Release(void *obj) { ((IUnknown *)obj)->Release(); }

int DeckLink_ListDevices(void **devices) {

  // Get devices
  auto _devices = DeckLinkManager::GetInstance()->GetDevices();

  // Set devices
  *devices = _devices->size() > 0 ? (void *)_devices->data() : nullptr;

  return int(_devices->size());
}

void *DeckLink_GetDevice(void **devices, int index) { return devices[index]; }

#if defined(WIN32)
BSTR DeckLink_GetDeviceModelName(void *device) {
  BSTR name = nullptr;
  if (device)
    ((IDeckLink *)device)->GetModelName(&name);
  return name;
}
#else
const char *DeckLink_GetDeviceModelName(void *device) {
  const char *name = "";
  if (device)
    ((IDeckLink *)device)->GetModelName(&name);
  return name;
}
#endif

#if defined(WIN32)
BSTR DeckLink_GetDeviceDisplayName(void *device) {
  BSTR name = nullptr;
  if (device)
    ((IDeckLink *)device)->GetDisplayName(&name);
  return name;
}
#else
const char *DeckLink_GetDeviceDisplayName(void *device) {
  const char *name = "";
  if (device)
    ((IDeckLink *)device)->GetDisplayName(&name);
  return name;
}
#endif

void *DeckLink_CreateInputStream(void *device) {
  return new DeckLinkInputStream((IDeckLink *)device);
}

void DeckLink_StartInputStream(void *stream) {
  ((DeckLinkInputStream *)stream)->Start();
}

void DeckLink_StopInputStream(void *stream) {
  ((DeckLinkInputStream *)stream)->Stop();
}

long long int DeckLink_GetInputStreamTimeStamp(void *stream) {
  return ((DeckLinkInputStream *)stream)->GetTimeStamp();
}

void *DeckLink_GetInputStreamVideoFrame(void *stream) {
  return (void *)((DeckLinkInputStream *)stream)->GetVideoFrame();
}

int DeckLink_GetInputStreamPixelFormat(void *stream) {
  return ((DeckLinkInputStream *)stream)->GetPixelFormat();
}

void DeckLink_SetInputStreamPixelFormat(void *stream, int pixelFormat) {
  ((DeckLinkInputStream *)stream)->SetPixelFormat(BMDPixelFormat(pixelFormat));
}

int DeckLink_GetVideoFrameWidth(void *frame) {
  return ((IDeckLinkVideoFrame *)frame)->GetWidth();
}

int DeckLink_GetVideoFrameHeight(void *frame) {
  return ((IDeckLinkVideoFrame *)frame)->GetHeight();
}

int DeckLink_GetVideoFrameRowBytes(void *frame) {
  return ((IDeckLinkVideoFrame *)frame)->GetRowBytes();
}

void *DeckLink_GetVideoFrameBytes(void *frame) {
  void *bytes = nullptr;
  ((IDeckLinkVideoFrame *)frame)->GetBytes(&bytes);
  return bytes;
}

int DeckLink_GetVideoFramePixelFormat(void *frame) {
  return ((IDeckLinkVideoFrame *)frame)->GetPixelFormat();
}

void *DeckLink_CreateOutputStream(void *device) {
  return new DeckLinkOutputStream((IDeckLink *)device);
}

void DeckLink_StartOutputStream(void *stream) {
  ((DeckLinkOutputStream *)stream)->Start();
}

void DeckLink_StopOuputStream(void *stream) {
  ((DeckLinkOutputStream *)stream)->Stop();
}

void DeckLink_AddOutputStreamVideoFrame(void *stream, void *data, int width,
                                        int height, int pixelFormat) {

  // Copy video frame
  auto videoFrame = new DeckLinkVideoFrame((uint8_t *)data, width, height,
                                           BMDPixelFormat(pixelFormat));

  // Add video frame
  ((DeckLinkOutputStream *)stream)->AddVideoFrame(videoFrame);
}
