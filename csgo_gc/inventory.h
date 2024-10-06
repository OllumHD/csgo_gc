#pragma once

#include "item_schema.h"
#include "random.h"

class KeyValue;

class Inventory
{
public:
    Inventory(uint64_t steamId);
    ~Inventory();

    void BuildCacheSubscription(CMsgSOCacheSubscribed &message, int level, bool server);

    bool EquipItem(uint64_t itemId, uint32_t classId, uint32_t slotId, CMsgSOMultipleObjects &update);

    bool UseItem(uint64_t itemId,
        CMsgSOSingleObject &destroy,
        CMsgSOMultipleObjects &updateMultiple,
        CMsgGCItemCustomizationNotification &notification);

private:
    uint32_t AccountId() const;

    // pass zero as highItemId to generate a new one
    CSOEconItem &CreateItem(uint32_t highItemId, CSOEconItem *copyFrom = nullptr);

    void ReadFromFile();
    void ReadItem(const KeyValue &itemKey, CSOEconItem &item) const;

    void WriteToFile() const;
    void WriteItem(KeyValue &itemKey, const CSOEconItem &item) const;

    // helper, only called via EquipItem
    // bool UnequipItem(uint64_t itemId, CMsgSOMultipleObjects &update);
    void UnequipItem(uint32_t classId, uint32_t slotId, CMsgSOMultipleObjects &update);

    const uint64_t m_steamId;
    ItemSchema m_itemSchema;
    Random m_random;
    uint32_t m_lastGeneratedHighItemId{ 1 };
    std::unordered_map<uint64_t, CSOEconItem> m_items;
    std::vector<CSOEconDefaultEquippedDefinitionInstanceClient> m_defaultEquips;
};