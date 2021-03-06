#pragma once

#include "CNShardServer.hpp"
#include "Player.hpp"

#include "contrib/JSON.hpp"

struct Reward {
    int32_t id;
    int32_t itemTypes[4];
    int32_t itemIds[4];
    int32_t money;
    int32_t fusionmatter;

    Reward(int32_t id, nlohmann::json types, nlohmann::json ids, int32_t m, int32_t fm) :
    id(id), money(m), fusionmatter(fm) {
        for (int i = 0; i < 4; i++) {
            itemTypes[i] = types[i];
            itemIds[i] = ids[i];
        }
    };
};

struct TaskData {
    /*
     * TODO: We'll probably want to keep only the data the server actually needs,
     *       but for now RE/development is much easier if we have everything at
     *       our fingertips.
     */
    nlohmann::json task;

    TaskData(nlohmann::json t) : task(t) {}

    // convenience
    auto operator[](std::string s) { return task[s]; }
};

namespace MissionManager {
    extern std::map<int32_t, Reward*> Rewards;
    extern std::map<int32_t, TaskData*> Tasks;
    void init();

    void taskStart(CNSocket* sock, CNPacketData* data);
    void taskEnd(CNSocket* sock, CNPacketData* data);
    void setMission(CNSocket* sock, CNPacketData* data);
    void quitMission(CNSocket* sock, CNPacketData* data);

    int findQSlot(Player *plr, int id);
    void dropQuestItem(CNSocket *sock, int task, int count, int id, int mobid);
    int giveMissionReward(CNSocket *sock, int task);

    void mobKilled(CNSocket *sock, int mobid);
}
