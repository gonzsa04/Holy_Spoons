#pragma once
#include <vector>
class GameObject;

class nap_Pool {
private:
	std::vector<GameObject*> pool;
	int defaultValue = 10;
	GameObject* spawn();
	GameObject* original = nullptr;

public:
	nap_Pool(std::string entity);
	virtual ~nap_Pool();

	GameObject* getItem();
	void init();

	std::vector<GameObject*> getPool() { return pool; };
	inline void setDefault(int def) { defaultValue = def; };
};

