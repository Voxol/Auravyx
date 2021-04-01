#pragma once
#include "World/Chunk.h"
#include <vector>
#include <memory>
#include "Engine/Camera.h"
#include <atomic>
#include "World/ChunkHeight.h"
class World
{
public:
	World();
	~World();

	std::vector<std::unique_ptr<Chunk>> overworld;

	std::vector<std::shared_ptr<ChunkHeight>> overworldHeightmap;

	std::atomic_int unloadLock = false;

	Model tMesh;

	void generate();

	void update();

	void create();

	void render(Camera * cam, Matrix4f* projectionMatrix);
	
	void addChunk(Chunk chunk);

	Chunk* getChunk(int x, int y, int z);

	std::shared_ptr<ChunkHeight> getChunkHeightmap(int x, int z);

	bool isLoaded(int x, int y, int z);

	void sphere(float xP, float yP, float zP, float radius, float power);

	void cuboid(float xP, float yP, float zP, float xS, float yS, float zS, float power);

	std::shared_ptr<World> getOverworld();

	void setVoxel(int x, int y, int z, int type, float density);

	void setOverworldTime(long long int time);

	long long int getOverworldTime();

	long long int getOverworldDayCycle();

	void test();

	Chunk *getChunk(int i);

	void setup();

private:

	long long int overworldDayCycle = 240000;

	long long int overworldTime = (long long int) (240000.0 * 10.32);
};

