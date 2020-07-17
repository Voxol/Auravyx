#include "testlib.h"

#define WAVEFILE      "boom.wav"
#define NUMSOURCES    15

static void iterate( void );

static ALuint multis[NUMSOURCES] = { 0 };

static ALCcontext *context;

static void iterate( void )
{
	int i;

	for ( i = 0; i < NUMSOURCES; i++ ) {
		if( sourceIsPlaying( multis[i] ) != AL_TRUE ) {
			alSourcePlay( multis[i] );
		}
		microSleep( 20000 );
	}

}

static void init( const ALbyte *fname )
{
	ALfloat zeroes[] = { 0.0f, 0.0f, 0.0f };
	ALfloat position[] = { 2.0f, 0.0f, 4.0f };
	ALuint boom;
	int i = 0;

	alListenerfv( AL_POSITION, zeroes );

	boom = CreateBufferFromFile( fname );

	alGenSources( NUMSOURCES, multis );

	alSourcefv( multis[0], AL_POSITION, position );
	alSourcei( multis[0], AL_BUFFER, boom );
	alSourcef( multis[i], AL_MAX_GAIN, 1.0 );
	alSourcef( multis[i], AL_REFERENCE_DISTANCE, 1.0 );

	for ( i = 1; i < NUMSOURCES; i++ ) {
		position[0] = -2.0f * i;
		position[1] = 0.0;
		position[2] = -4.0f * i;

		alSourcefv( multis[i], AL_POSITION, position );
		alSourcei( multis[i], AL_BUFFER, boom );
		alSourcef( multis[i], AL_MAX_GAIN, 0 );
		alSourcef( multis[i], AL_REFERENCE_DISTANCE, 0.1 );
	}
}

int main( int argc, char *argv[] )
{
	ALCdevice *device;
	int attributeList[] = { ALC_FREQUENCY, 22050, 0 };
	time_t start;
	time_t shouldend;

	start = time( NULL );
	shouldend = time( NULL );

	device = alcOpenDevice( NULL );
	if( device == NULL ) {
		return EXIT_FAILURE;
	}

	/* Initialize ALUT. */
	context = alcCreateContext( device, attributeList );
	if( context == NULL ) {
		alcCloseDevice( device );
		return EXIT_FAILURE;
	}

	alcMakeContextCurrent( context );

	testInitWithoutContext( &argc, argv );

	init( ( const ALbyte * ) ( ( argc == 1 ) ? WAVEFILE : argv[1] ) );

	while( shouldend - start < 30 ) {
		shouldend = time( NULL );

		iterate(  );
	}

	testExit();

	alcDestroyContext( context );
	alcCloseDevice( device );

	return EXIT_SUCCESS;
}
