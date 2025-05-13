#pragma once
class World;
class GameObject;
class Load
{
public:
	Load(World* _pWorld);
	~Load() { }

	void Update(); 

	static void LoadGameObjects(string _path, POINT _at = { 0,0 });
	static void LoadTileMapAt(string _path, POINT _at = { 0,0 });
	static void LoadPartSceneAt(string _path, POINT _at = { 0,0 });
	static void LoadBackgroundAt(string _path, POINT _at = { 0,0 });

	void CreatePlusDataMode(bool _b) { m_bCreatePlus = _b; }

private:
	void LoadGameObjectsOnUpdate(string _path, POINT _at = { 0,0 });
	void LoadTileMapOnUpdate(string _path, POINT _at);
	void LoadPartSceneOnUpdate(string _path, POINT _at = { 0,0 });
	void LoadBackgroundOnUpdate(string _path, POINT _at = { 0,0 });

	void DeleteTiles(GameObject*& _pTileObject);

private:
	bool m_bCreatePlus = true;
	static World* m_pWorld;

	static vector<string> m_gameobjectsPath;
	static vector<POINT> m_gameobjectsAt;

	static vector<string> m_tilemapPath;
	static vector<POINT> m_tilemapAt;

	static vector<string> m_partScenePath;
	static vector<POINT> m_partSceneAt;

	static vector<string> m_bgPath;
	static vector<POINT> m_bgAt;
};