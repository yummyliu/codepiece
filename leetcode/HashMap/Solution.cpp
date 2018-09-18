class MyHashMap {
	int hashmap[1000001];
	public:
	/** Initialize your data structure here. */
	MyHashMap() {
		memset(hashmap, -1, sizeof(hashmap));
	}

	/** value will always be non-negative. */
	void put(int key, int value) {
		    hashmap[key] = value;
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		    return hashmap[key];
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		    hashmap[key] = -1;
	}
};
