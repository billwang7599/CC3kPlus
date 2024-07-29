
class Entity;
class EntityManager;

class CombatSystem {
    public:
    void attack(Entity&, Entity&);
    // void enemy_attack(const EntityManager&);  -- make an AI/enemy system
    void lifesteal(Entity&, int);
    void goldsteal(Entity&, Entity&);
};