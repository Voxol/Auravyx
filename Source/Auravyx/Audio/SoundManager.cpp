#include "Auravyx/Audio/SoundManager.h"
#include "AL/al.h"
#include "AL/alc.h"
#include <iostream>
#include "Logger/Log.h"
#include "AL/efx.h"
#include <vector>
#include "Auravyx/Core/Assets.h"
#include <Auravyx/Audio/Sound.h>
#include "Auravyx/Utility/Math/M.h"
#include <Auravyx/Graphics/GFX.h>
#include <string.h>
#include <cmath>
#define AL_ALEXT_PROTOTYPES
#define ALC_EXT_EFX 
SoundManager::SoundManager()
{
}
SoundManager* SoundManager::soundManager;
SoundManager::SoundManager(SoundManager* s)
{
	soundManager = s;
}


SoundManager::~SoundManager()
{
}

ALCdevice* device;
ALCcontext* context;
const ALCchar* list_audio_devices(const ALCchar* devices)
{
	const ALCchar* device = devices, * next = devices + 1;

	size_t len = 0;

	int i = 0;
	std::vector<std::string> listedDevices;

	while (device && *device != '\0' && next && *next != '\0')
	{
		listedDevices.emplace_back(std::string(device));
		if (i == 1)
		{
			//return device;
		}

		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
		i++;
	}

	if (listedDevices.size() != 0)
	{
		Log::out("OpenAL", std::to_string(listedDevices.size()) + " devices detected, if device is missing, make sure it is enabled.", GREEN);
		for (auto d : listedDevices)
		{
			Log::out("         - " + d);
		}
	}
	else
	{
		Log::out("OpenAL", "No audio devices detected, make sure there are enabled devices.", GREEN);
	}
	return NULL;
}

void SoundManager::start()
{
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    const char * deviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    Log::out("[OpenAL] Default device: " + std::string(deviceName));
	if (enumeration == AL_FALSE)
	{
		Log::out("[OpenAL] No enumeration extension");
	}
	device = NULL;
	if (!device)
	{
		device = alcOpenDevice(NULL);
	}
	const ALchar* name;
	name = NULL;
	if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
	{
		name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
	}
	if (!name || alcGetError(device) != AL_NO_ERROR)
	{
		name = alcGetString(device, ALC_DEVICE_SPECIFIER);
	}
	if (!device)
	{
		Log::out("[OpenAL] Error with device " + std::string(name));

		Log::criticalError("[OpenAL] No playback devices found! No audio will be available.");
		return;
	}
	context = alcCreateContext(device, NULL);
	if (context == NULL || alcMakeContextCurrent(context) == ALC_FALSE)
	{
		Log::out("[OpenAL] Error with context");
		if (context != NULL)
		{
			alcDestroyContext(context);
		}
		alcCloseDevice(device);
		return;
	}
	alListenerf(AL_GAIN, 1);
	alDopplerFactor(1);
	alDistanceModel(AL_INVERSE_DISTANCE);
	//alEffectf(AL_AIR_ABSORPTION_FACTOR, AL_EFFECT_TYPE, 100);
	std::string alVersion = alGetString(AL_VERSION);
	std::string alVendor = alGetString(AL_VENDOR);
	std::string alRenderer = alGetString(AL_RENDERER);
	Log::out("OpenAL", "Version: " + alVersion + ", Vendor: " + alVendor + ", Renderer: " + alRenderer, GREEN);
	name = list_audio_devices(alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER));
}

void SoundManager::stop()
{
	destroyAllSounds();
	Assets::getAssets()->getAssets()->deleteAudio();

	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void SoundManager::destroyAllSounds()
{
	for (auto s : sounds)
	{
		alDeleteSources(1, &s);
	}
	sounds.clear();
}

void SoundManager::addSound(const ALuint source)
{
	sounds.insert(source);
}

void SoundManager::removeSound(const ALuint source)
{
	sounds.erase(source);
}

void SoundManager::setListener(const Camera& camera)
{
	alListener3f(AL_POSITION, camera.x, camera.y, camera.z);
	alListener3f(AL_VELOCITY, camera.xVel, camera.yVel, camera.zVel);

	Vec3f normalizedRotation = Vec3f(-sin(M::toRadians(GFX::getOverlay()->CAM.yRot)) * (cos(M::toRadians(GFX::getOverlay()->CAM.xRot))),
		sin(M::toRadians(GFX::getOverlay()->CAM.xRot)),
		-cos(M::toRadians(GFX::getOverlay()->CAM.yRot)) * (cos(M::toRadians(GFX::getOverlay()->CAM.xRot))));

	Vec3f normalizedUpRotation = Vec3f(sin(M::toRadians(GFX::getOverlay()->CAM.yRot)) * (sin(M::toRadians(GFX::getOverlay()->CAM.xRot))),
		cos(M::toRadians(GFX::getOverlay()->CAM.xRot)),
		cos(M::toRadians(GFX::getOverlay()->CAM.yRot)) * (sin(M::toRadians(GFX::getOverlay()->CAM.xRot))));

	float orientation[] = { normalizedRotation.x, normalizedRotation.y, normalizedRotation.z,
	normalizedUpRotation.x, normalizedUpRotation.y, normalizedUpRotation.z };

	/*Matrix4f viewMatrix = GFX::getOverlay()->CAM.getViewMatrix();
	Vec3f forwardVec = Vec3f(viewMatrix.m20, viewMatrix.m21, viewMatrix.m22);
	Vec3f upVec = Vec3f(viewMatrix.m10, viewMatrix.m11, viewMatrix.m12);
	float orientation[] = { forwardVec.x, -forwardVec.y, -forwardVec.z,
	upVec.x, upVec.y, upVec.z };*/
	alListenerfv(AL_ORIENTATION, orientation);
}

SoundManager* SoundManager::getSoundManager()
{
	return soundManager;
}
